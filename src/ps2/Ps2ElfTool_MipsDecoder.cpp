#include "Ps2ElfTool_MipsDecoder.h"

#define GPREG(x) g_MipsRegistersGP[inst->args[x].value]
#define FPREG(x) g_MipsRegistersFP[inst->args[x].value]
#define VFPREG(x) g_MipsRegistersVFP[inst->args[x].value]
#define COP0REG(x) g_MipsRegistersCOP0[inst->args[x].value]
#define COP1REG(x) g_MipsRegistersCOP1[inst->args[x].value]
#define COP2REG(x) g_MipsRegistersCOP2[inst->args[x].value]

#define BRANCH(pc, off) ((pc + 4) + (((s32)off) << 2))
#define JUMP(pc, target) (((pc + 4) & 0xF0000000 ) | ((s32)target << 2))

String8 _immediate(u16 value)
{
    if(value == 0x8000) return "0x8000";
    if(value & 0x8000) {
        return String8::Format("-0x%04x", (s16)((~value) + 1));
    }
    return String8::Format("0x%04x", value);
}

String8 _getMask(MipsInstruction* inst) {
    u32 dest = inst->args[MIPS_ARG_RS].value & 0x0F;
    String8 mask = "";
    if(dest & 0b1000) mask += "x";
    if(dest & 0b0100) mask += "y";
    if(dest & 0b0010) mask += "z";
    if(dest & 0b0001) mask += "w";

    return String8::Format("%s.%s", inst->mnemonic, mask.Cstr());
}

MipsDecoder::MipsDecoder()
{
    this->ip = nullptr;
    this->start = 0;
    this->pc = this->start;
}

MipsDecoder::MipsDecoder(ByteArray data, u32 start)
{
    this->data = data;
    this->ip = (u32*)(this->data.Cptr());

    this->start = start;
    this->pc = this->start;
}

int MipsDecoder::Next() 
{
    if (this->ip == (u32*)(data.Cptr() + data.Size())) 
        return -1;
    this->ip++;
    this->pc += 4;
    return 0;
}

void MipsDecoder::MovePC(u32 address)
{
    this->pc = address;
}
void MipsDecoder::LoadData(ByteArray data, u32 start)
{
    this->data = data;
    this->start = start;
    this->pc = start;
    this->ip = (u32*)this->data.Cptr();
}

MipsInstruction MipsDecoder::Decode()
{
    return DecodeInstruction(*ip);
}

void MipsDecoder::MoveToStart() 
{ 
    if (this->data.Cptr() == nullptr) return;
    this->ip = (u32*)this->data.Cptr(); 
    this->pc = this->start;
}

bool MipsDecoder::AtEnd()
{
    return (u8*)ip >= data.Cptr() + data.Size();
}

void MipsDecoder::Parse()
{
    if (this->data.Cptr() == nullptr) return;
    MoveToStart();
    u32 idx = 0;
    while (!AtEnd()) {
        MipsInstruction inst = Decode();
        if (inst.layout == OL_TARGET) {
            u32 addr = JUMP(pc, inst.args[MIPS_ARG_TARGET].value);
            AsmLabel lbl;
            if (String8(inst.mnemonic).ToLower() == "jal")
                lbl.name = String8::Format("FUN_%08x", addr);
            else
                lbl.name = String8::Format("LAB_%08x", addr);
            lbl.address = addr;
            labels.Add(lbl);
        }
        else if (inst.layout == OL_R_TARGET || inst.layout == OL_RR_TARGET) {
            u32 addr = BRANCH(pc, (s16)inst.args[MIPS_ARG_IMM].value);
            AsmLabel lbl;
            lbl.name = String8::Format("LAB_%08x", addr);
            lbl.address = addr;
            labels.Add(lbl);
        }
        Next();
    }
}

MipsInstruction MipsDecoder::DecodeInstruction(u32 instruction)
{
    MipsInstruction inst;
    inst.type = ITYPE_INVALID;
    inst.args[0].type = AT_NULL;
    inst.mnemonic = "";
    inst.layout = OL_NONE;

    if(instruction == 0x00000000) {
        inst = InstNop;
        return inst;
    }

    MipsInstruction* iptr = FindInstruction(instruction);

    if(iptr == nullptr) return inst;

    inst = *iptr;
    u8 shift = 26;

    for(MipsArgument* arg = inst.args; arg->type != AT_NULL; arg++) {
        shift -= arg->bits;
        arg->value = (instruction >> shift) & ((1 << arg->bits) - 1);
    }

    return inst;
}

String8 MipsDecoder::GetInstructionAsm(u32 pc, MipsInstruction* inst)
{
    String8 out = "";

    if (inst->type == ITYPE_INVALID) {
        out = "";
        return out;
    }

    switch (inst->layout) {
        case OL_NONE: {
            out = inst->mnemonic;
        } break;

        case OL_R: {
            out = String8::Format("%s $%s", inst->mnemonic, GPREG(MIPS_ARG_RS));
        } break;

        case OL_RR: {
            if (inst->args[MIPS_ARG_RD].value == 31) {
                out = String8::Format("%s $%s", inst->mnemonic, GPREG(MIPS_ARG_RS));
            } else {
                out = String8::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RS));
            }
        } break;

        case OL_RI: { // Used for LUI ($rt, imm)
            out = String8::Format("%s $%s, 0x%04x", inst->mnemonic, GPREG(MIPS_ARG_RT), inst->args[MIPS_ARG_IMM].value);
        } break;

        case OL_RSI: { // Used for MTSAH / MTSAB ($rs, imm)
            out = String8::Format("%s $%s, %s", inst->mnemonic, GPREG(MIPS_ARG_RS), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr());
        } break;

        case OL_RRR: {
            out = String8::Format("%s $%s, $%s, $%s", inst->mnemonic,
                                  GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT));
        } break;

        case OL_RFR: { // mtc1 / mfc1 (\(rt = GPR,\)fs = FPR)
            out = String8::Format("%s  $%s, $%s", inst->mnemonic,
                                  GPREG(MIPS_ARG_RT), FPREG(MIPS_ARG_FS));
        } break;

        case OL_FRFR: { // cvt.s, mov.s, sqrt.s (\(fd,\)fs)
            out = String8::Format("%s $%s, $%s", inst->mnemonic,
                                  FPREG(MIPS_ARG_FD), FPREG(MIPS_ARG_FS));
        } break;

        case OL_FRFRFR: { // add.s, sub.s, mul.s (\(fd,\)fs, $ft)
            out = String8::Format("%s $%s, $%s, $%s", inst->mnemonic,
                                  FPREG(MIPS_ARG_FD), FPREG(MIPS_ARG_FS), FPREG(MIPS_ARG_FT));
        } break;

        case OL_RVR: { // qmtc2 / qmfc2 (\(rt = GPR,\)vf = Vector Reg)
            out = String8::Format("%s $%s, $%s", inst->mnemonic,
                                  GPREG(MIPS_ARG_RT), VFPREG(MIPS_ARG_RD));
        } break;

        case OL_VRVR: {
            out = String8::Format("%s $%s, $%s", _getMask(inst).Cstr(),
                                  VFPREG(MIPS_ARG_FS), VFPREG(MIPS_ARG_FT));
        } break;

        case OL_AVRVR: {
            if(String8(inst->mnemonic).EndsWith("i")) {
                out = String8::Format("%s $ACC, $%s, $I", _getMask(inst).Cstr(),
                                      VFPREG(MIPS_ARG_FS));
            }
            else if(String8(inst->mnemonic).EndsWith("q")) {
                out = String8::Format("%s $ACC, $%s, $Q", _getMask(inst).Cstr(),
                                      VFPREG(MIPS_ARG_FS));
            }
            else
                out = String8::Format("%s $ACC, $%s, $%s", _getMask(inst).Cstr(),
                                  VFPREG(MIPS_ARG_FS), VFPREG(MIPS_ARG_FT));
        } break;

        case OL_VRVRVR: {
            // Check if mnemonic ends with 'i' (vaddi, vmaddi, etc.)
            if (String8(inst->mnemonic).EndsWith("i")) {
                out = String8::Format("%s $%s, $%s, $I", _getMask(inst).Cstr(),
                                      VFPREG(MIPS_ARG_FD), VFPREG(MIPS_ARG_FS));
            }
            // Check if mnemonic ends with 'q' (vaddq, vmulq, etc.)
            else if (String8(inst->mnemonic).EndsWith("q")) {
                out = String8::Format("%s $%s, $%s, $Q", _getMask(inst).Cstr(),
                                      VFPREG(MIPS_ARG_FD), VFPREG(MIPS_ARG_FS));
            }
            // Standard 3-vector operation
            else {
                out = String8::Format("%s $%s, $%s, $%s", _getMask(inst).Cstr(),
                                      VFPREG(MIPS_ARG_FD), VFPREG(MIPS_ARG_FS), VFPREG(MIPS_ARG_FT));
            }
        } break;

        case OL_RC0: { // mfc0 / mtc0 (\(rt = GPR,\)rd = CP0 Reg)
            out = String8::Format("%s $%s, $%s", inst->mnemonic,
                                  GPREG(MIPS_ARG_RT), COP0REG(MIPS_ARG_RD));
        } break;

        case OL_RC1: { // cfc1 / ctc1 (\(rt = GPR,\)fcr = FPC Reg)
            out = String8::Format("%s $%s, $%s", inst->mnemonic,
                                  GPREG(MIPS_ARG_RT), COP1REG(MIPS_ARG_RD));
        } break;

        case OL_RC2: { // cfc2 / ctc2 (\(rt = GPR,\)vi = VU0 Control Reg)
            out = String8::Format("%s $%s, $%s", inst->mnemonic,
                                  GPREG(MIPS_ARG_RT), COP2REG(MIPS_ARG_RD));
        } break;

        case OL_RRI: {
            out = String8::Format("%s $%s, $%s, 0x%04x", inst->mnemonic,
                                  GPREG(MIPS_ARG_RT), GPREG(MIPS_ARG_RS), inst->args[MIPS_ARG_IMM].value);
        } break;

        case OL_RR_OFFSET: {
            out = String8::Format("%s $%s, %s($%s)", inst->mnemonic,
                                  GPREG(MIPS_ARG_RT), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr(), GPREG(MIPS_ARG_RS));
        } break;

        case OL_FRR_OFFSET: {
            out = String8::Format("%s $%s, %s($%s)", inst->mnemonic,
                                  FPREG(MIPS_ARG_RT), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr(), GPREG(MIPS_ARG_RS));
        } break;

        case OL_VRR_OFFSET: {
            out = String8::Format("%s $%s, %s($%s)", inst->mnemonic,
                                  VFPREG(MIPS_ARG_RT), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr(), GPREG(MIPS_ARG_RS));
        } break;

        case OL_RR_TARGET: {
            out = String8::Format("%s $%s, $%s, 0x%08x", inst->mnemonic,
                                  GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT), BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value));
        } break;

        case OL_R_TARGET: {
            out = String8::Format("%s $%s, 0x%08x", inst->mnemonic,
                                  GPREG(MIPS_ARG_RS), BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value));
        } break;

        case OL_TARGET: {
            out = String8::Format("%s 0x%08x", inst->mnemonic, JUMP(pc, inst->args[MIPS_ARG_TARGET].value));
        } break;

        case OL_RR_SHIFT: {
            out = String8::Format("%s $%s, $%s, %d", inst->mnemonic,
                                  GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RT), inst->args[MIPS_ARG_IMM].value);
        } break;

        case OL_HINT: {
            out = String8::Format("%s %d, %s($%s)", inst->mnemonic,
                inst->args[MIPS_ARG_RT].value, _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr(), GPREG(MIPS_ARG_RS));
        } break;

        case OL_SYNC: {
            u8 stype = inst->args[MIPS_ARG_SHAMT].value;
            if(stype == 0x00) {
                out = "sync";
            }
            else if(stype == 0x10) {
                out = "sync.p";
            }
            else {
                out = String8::Format("%s 0x%02x", inst->mnemonic, stype);
            }
        } break;

        default: {
            out = "";
        } break;
    }

    return out;
}

u32 MipsDecoder::GetCurrentInstBytes()
{
    return *ip;
}

String8 MipsDecoder::GetCurrentAsm()
{
    MipsInstruction decoded = Decode();
    MipsInstruction* inst = &decoded;
    String8 out = "";
    switch (inst->layout) {
    case OL_RR_TARGET: {
        u32 target = BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value);
        s64 ilbl = findLabel(target);
        if (ilbl >= 0) {
            out = String8::Format("%s $%s, $%s, %s", inst->mnemonic,
                GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT), labels[ilbl].name.Cstr());
        }
        else
            out = String8::Format("%s $%s, $%s, 0x%08x", inst->mnemonic,
                GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT), target);
    } break;
    case OL_R_TARGET: {
        u32 target = BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value);
        s64 ilbl = findLabel(target);
        if (ilbl >= 0) {
            out = String8::Format("%s $%s, %s", inst->mnemonic,
                GPREG(MIPS_ARG_RS), labels[ilbl].name.Cstr());
        }
        else
            out = String8::Format("%s $%s, 0x%08x", inst->mnemonic,
                GPREG(MIPS_ARG_RS), target);
    } break;
    case OL_TARGET: {
        u32 target = JUMP(pc, inst->args[MIPS_ARG_TARGET].value);
        s64 ilbl = findLabel(target);
        if (ilbl >= 0) {
            out = String8::Format("%s %s", inst->mnemonic, labels[ilbl].name.Cstr());
        }
        else
            out = String8::Format("%s 0x%08x", inst->mnemonic, inst->args[MIPS_ARG_TARGET]);
    } break;
    default: {
        return GetInstructionAsm(this->pc, inst);
    } break;
    }
    return out;
}

List<String8> MipsDecoder::GetAsm()
{
    List<String8> out;
    if (data.Cptr() == nullptr) return out;

    u64 tenth = (data.Size()/4) / 100;

    u32 i = 1;
    u32 t = 0;

    MoveToStart();
    while (!AtEnd()) {
        s64 ilbl = findLabel(pc);
        if (ilbl >= 0) {
            out.Add(labels[ilbl].name + ":");
        }
        String8 instasm = GetCurrentAsm();
        if(instasm.Length() == 0) {
            out.Add(String8::Format("    Unknown Instruction (pc = 0x%08x , inst = 0x%08x)", pc, *ip));
        }
        out.Add("    " + instasm);
#if 0
        i++;
        if (i % tenth == 0) {
            t++;
            printf("%d%% disassembled.\n", t);
        }
#endif
        Next();
    }

    return out;
}

s64 MipsDecoder::findLabel(u32 address)
{
    for (int i = 0; i < labels.Size(); i++) {
        if (labels[i].address == address) {
            return i;
        }
    }
    return -1;
}

void MipsDecoder::CreateLabel(u32 address, String8 name)
{
    if (this->data.Size() == 0) return;
    for (int i = 0; i < labels.Size(); i++) {
        if (labels[i].address == address) 
            return;
    }
    AsmLabel lbl;
    lbl.address = address;
    lbl.name = name;
    labels += lbl;
}
