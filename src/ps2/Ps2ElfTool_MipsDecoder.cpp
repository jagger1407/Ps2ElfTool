#include "Ps2ElfTool_MipsDecoder.h"

#define GPREG(x) g_MipsRegistersGP[inst->args[x].value]
#define FPREG(x) g_MipsRegistersFP[inst->args[x].value]
#define VFPREG(x) g_MipsRegistersVFP[inst->args[x].value]
#define COP0REG(x) g_MipsRegistersCOP0[inst->args[x].value]
#define COP1REG(x) g_MipsRegistersCOP1[inst->args[x].value]
#define COP2REG(x) g_MipsRegistersCOP2[inst->args[x].value]

#define BRANCH(pc, off) ((pc + 4) + (((s32)off) << 2))
#define JUMP(pc, target) (((pc + 4) & 0xF0000000 ) | ((s32)target << 2))

String _immediate(u16 value)
{
    if(value == 0x8000) return "0x8000";
    if(value & 0x8000) {
        return String::Format("-0x%04x", (s16)((~value) + 1));
    }
    return String::Format("0x%04x", value);
}

String _getMask(MipsInstruction* inst) {
    u32 dest = inst->args[MIPS_ARG_RS].value & 0x0F;
    String mask = "";
    if(dest & 0b1000) mask += "x";
    if(dest & 0b0100) mask += "y";
    if(dest & 0b0010) mask += "z";
    if(dest & 0b0001) mask += "w";

    return String::Format("%s.%s", inst->mnemonic, mask.Cstr());
}

MipsDecoder::MipsDecoder()
{

}

MipsDecoder::MipsDecoder(ByteArray data, u32 start)
{
    LoadData(data, start);
}

void MipsDecoder::LoadData(ByteArray data, u32 start)
{
    this->data.Initialize((data.Size() + 3) & ~3);
    NCopy(this->data.Cptr(), data.Cptr(), data.Size());
    this->lbls.Initialize(data.Size());
    NZero(this->lbls.Cptr(), data.Size());
    this->ip = (u32*)this->data.Cptr();
    this->pc = start;
    this->start = start;
}

void MipsDecoder::MoveToStart()
{
    this->ip = (u32*)this->data.Cptr();
    this->pc = this->start;
}

u32 MipsDecoder::Next()
{
    this->ip++;
    this->pc += 4;
    return *this->ip;
}

bool MipsDecoder::AtEnd()
{
    return this->pc >= this->start + this->data.Size();
}

void MipsDecoder::AnalyzeLabels()
{
    if(this->data.Size() == 0) return;

    u64 size = lbls.Size();

    MoveToStart();

    while(!AtEnd()) {
        u32 cur = *this->ip;
        MipsInstruction inst;
        DecodeInstruction(&inst, cur);

        if(inst.layout == OL_TARGET) {
            u32 addr = JUMP(pc, inst.args[MIPS_ARG_TARGET].value);
            u32 offset = addr - start;
            if(offset < size) {
                if(*inst.mnemonic == 'j') {
                    lbls[offset] = LBL_FUN;
                }
                else if(lbls[offset] != LBL_FUN) {
                    lbls[offset] = LBL_LAB;
                }
            }
        }
        else if(inst.layout == OL_RS_RT_IMM || (inst.layout == OL_RS_IMM && *inst.mnemonic == 'b')) {
            u32 addr = BRANCH(pc, (s16)inst.args[MIPS_ARG_IMM].value);
            u32 offset = addr - start;
            if(offset < size && lbls[offset] != LBL_FUN) {
                lbls[offset] = LBL_LAB;
            }
        }
        // TODO: Generate DAT Labels for data sections

        Next();
    }
}

List<String> MipsDecoder::GetAsm()
{
    List<String> out;
    if(this->data.Size() == 0) return out;

    const char* lblprefix[4] = { "0x", "LAB_", "FUN_", "DAT" };

    MoveToStart();

    while(!AtEnd()) {
        String line;
        u32 loc = pc - start;

        if(lbls[loc] != LBL_NONE) {
            out += String::Format("%s%08x:", lblprefix[lbls[loc]], loc + start);
        }

        MipsInstruction rawinst;
        MipsInstruction* inst = &rawinst;
        DecodeInstruction(inst, *ip);

        // TODO: Find a better way of adding the labels

        if(inst->layout == OL_TARGET) {
            u32 addr = JUMP(pc, inst->args[MIPS_ARG_TARGET].value);
            u32 offset = addr - start;
            if(offset < lbls.Size())
                line = String::Format("%s %s%08x", inst->mnemonic, lblprefix[lbls[offset]], addr);
            else
                line = String::Format("%s 0x%08x", inst->mnemonic, addr);
        }
        else if(inst->layout == OL_RS_RT_IMM) {
            u32 addr = BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value);
            u32 offset = addr - start;
            if(offset < lbls.Size()) {
                line = String::Format("%s $%s, $%s, %s%08x", inst->mnemonic,
                                      GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT), lblprefix[lbls[offset]], addr);
            }
            else
                line = String::Format("%s $%s, $%s, 0x%08x", inst->mnemonic,
                                      GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT), addr);
        }
        else if(inst->layout == OL_RS_IMM && *inst->mnemonic == 'b') {
            u32 addr = BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value);
            u32 offset = addr - start;
            // bcNf or bcNt and likely variants don't use the RS reg
            if(inst->opcode >= 0x10 && inst->opcode <= 0x12) {
                if(offset < lbls.Size()) {
                    line = String::Format("%s %s%08x", inst->mnemonic, lblprefix[lbls[offset]], addr);
                }
                else
                    line = String::Format("%s 0x%08x", inst->mnemonic, addr);
            }
            else if(offset < lbls.Size()) {
                line = String::Format("%s $%s, %s%08x", inst->mnemonic, GPREG(MIPS_ARG_RS), lblprefix[lbls[offset]], addr);
            }
            else
                line = String::Format("%s $%s, 0x%08x", inst->mnemonic, GPREG(MIPS_ARG_RS), addr);
        }
        else {
            line = GetInstructionAsm(inst, pc);
            if(line.Length() == 0)
                line = String::Format(".word 0x%08x", *ip);
        }

        out += "    " + line;

        Next();
    }
    return out;
}

void MipsDecoder::DecodeInstruction(MipsInstruction* inst, u32 instruction)
{
    if(inst == nullptr) return;
    inst->type = ITYPE_INVALID;
    inst->args[0].type = AT_NULL;
    inst->mnemonic = "";
    inst->layout = OL_NONE;

    if(instruction == 0x00000000) {
        *inst = InstNop;
        return;
    }

    MipsInstruction* iptr = FindInstruction(instruction);

    if(iptr == nullptr) return;

    *inst = *iptr;
    u8 shift = 26;

    for(MipsArgument* arg = inst->args; arg->type != AT_NULL; arg++) {
        shift -= arg->bits;
        arg->value = (instruction >> shift) & ((1 << arg->bits) - 1);
    }

    return;
}

String MipsDecoder::GetInstructionAsm(MipsInstruction* inst, u32 pc)
{
    String out = "";

    if (inst->type == ITYPE_INVALID) {
        out = "";
        return out;
    }

    switch (inst->layout) {
        case OL_NONE: { // Used for nop or syscall
            out = inst->mnemonic;
        } break;
        case OL_CALL: {
            out = inst->mnemonic;
            u32 code1 = inst->args[MIPS_ARG_SHAMT].value;
            code1 += inst->args[MIPS_ARG_RD].value << 5;
            u32 code2 = inst->args[MIPS_ARG_RT].value;
            code2 += inst->args[MIPS_ARG_RS].value << 5;
            if(code1 > 0) {
                out += String::Format(" 0x%x, 0x%x", code2, code1);
            }
        } break;
        case OL_RD: { // Used for mflo
            out = String::Format("%s $%s", inst->mnemonic, GPREG(MIPS_ARG_RD));
        } break;
        case OL_RS: { // Used for mtlo
            out = String::Format("%s $%s", inst->mnemonic, GPREG(MIPS_ARG_RS));
        } break;
        case OL_RD_RS: { // Used for jalr
            if (inst->args[MIPS_ARG_RD].value == 31) {
                out = String::Format("%s $%s", inst->mnemonic, GPREG(MIPS_ARG_RS));
            } else {
                out = String::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RS));
            }
        } break;
        case OL_RS_RT: { // Used for div
            out = String::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT));
        } break;
        case OL_RD_RT: { // Used for pabsw
            out = String::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RT));
        } break;
        case OL_RT_RD: { // Used for mfc0
            if(String(inst->mnemonic).EndsWith("0")) {
                out = String::Format("%s $%s, $%d", inst->mnemonic, GPREG(MIPS_ARG_RT), inst->args[MIPS_ARG_RD].value);
            }
            else
                out = String::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RT), FPREG(MIPS_ARG_RD));
        } break;
        case OL_RT_IMM: { // Used for lui
            out = String::Format("%s $%s, 0x%04x", inst->mnemonic, GPREG(MIPS_ARG_RT), inst->args[MIPS_ARG_IMM].value);
        } break;
        case OL_RS_IMM: { // Used for blez
            if(*inst->mnemonic == 'b')
                out = String::Format("%s $%s, 0x%08x", inst->mnemonic, GPREG(MIPS_ARG_RS), BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value));
            else
                out = String::Format("%s $%s, %s", inst->mnemonic, GPREG(MIPS_ARG_RS), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr());
        } break;
        case OL_RD_RT_SA: { // Used for sll
            out = String::Format("%s $%s, $%s, %d", inst->mnemonic,
                                 GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RT), inst->args[MIPS_ARG_SHAMT].value);
        } break;

        case OL_TARGET: { // Used for jal
            out = String::Format("%s 0x%08x", inst->mnemonic, JUMP(pc, inst->args[MIPS_ARG_TARGET].value));
        } break;
        case OL_RT_OFFSET: { // Used for lw
            out = String::Format("%s $%s, %s($%s)", inst->mnemonic,
                                 GPREG(MIPS_ARG_RT), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr(), GPREG(MIPS_ARG_RS));
        } break;
        case OL_RD_RS_RT: { // used for and
            out = String::Format("%s $%s, $%s, $%s", inst->mnemonic,
                                 GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT));
        } break;
        case OL_RD_RT_RS: { // Used for srlv
            out = String::Format("%s $%s, $%s, $%s", inst->mnemonic,
                                 GPREG(MIPS_ARG_RD), GPREG(MIPS_ARG_RT), GPREG(MIPS_ARG_RS));
        } break;
        case OL_RS_RT_IMM: { // Used for beq
            out = String::Format("%s $%s, $%s, 0x%08x", inst->mnemonic, GPREG(MIPS_ARG_RS), GPREG(MIPS_ARG_RT), BRANCH(pc, (s16)inst->args[MIPS_ARG_IMM].value));
        } break;
        case OL_RT_RS_IMM: { // Used for andi
            String name = inst->mnemonic;
            if(name == "andi" || name == "ori" || name == "xori")
                out = String::Format("%s $%s, $%s, 0x%04x", inst->mnemonic, GPREG(MIPS_ARG_RT), GPREG(MIPS_ARG_RS), (u16)inst->args[MIPS_ARG_IMM].value);
            else
                out = String::Format("%s $%s, $%s, %s", inst->mnemonic, GPREG(MIPS_ARG_RT), GPREG(MIPS_ARG_RS), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr());
        } break;
        case OL_RT_FS: { // Used for mfc1
            out = String::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RT), FPREG(MIPS_ARG_FS));
        } break;
        case OL_FD_FS: { // Used for abs.s
            out = String::Format("%s $%s, $%s", inst->mnemonic, FPREG(MIPS_ARG_FD), FPREG(MIPS_ARG_FS));
        } break;
        case OL_FS_FT: { // Used for c.lt.s
            out = String::Format("%s $%s, $%s", inst->mnemonic, FPREG(MIPS_ARG_FS), FPREG(MIPS_ARG_FT));
        } break;
        case OL_RT_VD: { // Used for qmtc2
            if(*inst->mnemonic == 'q') {
                out = String::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RT), VFPREG(MIPS_ARG_RD));
            }
            else
                out = String::Format("%s $%s, $%s", inst->mnemonic, GPREG(MIPS_ARG_RT), COP2REG(MIPS_ARG_RD));
        } break;
        case OL_FD_FT: { // Used for sqrt.s for some reason
            out = String::Format("%s $%s, $%s", inst->mnemonic, FPREG(MIPS_ARG_FD), FPREG(MIPS_ARG_FT));
        } break;
        case OL_FT_OFFSET: { // Used for lwc1
            out = String::Format("%s $%s, %s($%s)", inst->mnemonic,
                                 FPREG(MIPS_ARG_FT), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr(), GPREG(MIPS_ARG_RS));
        } break;
        case OL_FD_FS_FT: {
            out = String::Format("%s $%s, $%s, $%s", inst->mnemonic, FPREG(MIPS_ARG_FD), FPREG(MIPS_ARG_FS), FPREG(MIPS_ARG_FT));
        } break;
        case OL_VT_VS: {
            String name = inst->mnemonic;
            if(name.EndsWith("i")) {
                out = String::Format("%s $%s, $%s", _getMask(inst).Cstr(), COP2REG(MIPS_ARG_FT), COP2REG(MIPS_ARG_FS));
            }
            else if(name == "vmfir") {
                out = String::Format("%s $%s, $%s", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FT), COP2REG(MIPS_ARG_FS));
            }
            else
                out = String::Format("%s $%s, $%s", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FT), VFPREG(MIPS_ARG_FS));
        } break;
        case OL_VS_VIT_INC: {
            out = String::Format("%s $%s, ($%s++)", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FS), COP2REG(MIPS_ARG_FT));
        } break;
        case OL_VS_VIT_DEC: {
            out = String::Format("%s $%s, (--$%s)", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FT), COP2REG(MIPS_ARG_FS));
        } break;
        case OL_VT_VIS_INC: {
            out = String::Format("%s $%s, ($%s++)", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FT), COP2REG(MIPS_ARG_FS));
        } break;
        case OL_VT_VIS_DEC: {
            out = String::Format("%s $%s, (--$%s)", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FS), COP2REG(MIPS_ARG_FT));
        } break;
        case OL_VIT_VSF: {
            const char* comp = "xyzw";
            s32 fsf = inst->args[MIPS_ARG_RS].value & 0b11;
            out = String::Format("%s $%s, $%s%c", inst->mnemonic, COP2REG(MIPS_ARG_FS), VFPREG(MIPS_ARG_FT), comp[fsf]);
        } break;
        case OL_VT_OFFSET: {
            out = String::Format("%s $%s, %s($%s)", inst->mnemonic,
                                 VFPREG(MIPS_ARG_FT), _immediate((u16)inst->args[MIPS_ARG_IMM].value).Cstr(), GPREG(MIPS_ARG_RS));
        } break;
        case OL_VD_VS_VT: {

            if(inst->mnemonic[0] == 'v' && inst->mnemonic[1] == 'i') {
                out = String::Format("%s $%s, $%s, $%s", _getMask(inst).Cstr(), COP2REG(MIPS_ARG_FD), COP2REG(MIPS_ARG_FS), COP2REG(MIPS_ARG_FT));
            }
            else {
                if(String(inst->mnemonic).EndsWith("q")) {
                    out = String::Format("%s $%s, $%s, $Q", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FD), VFPREG(MIPS_ARG_FS));
                }
                else
                    out = String::Format("%s $%s, $%s, $%s", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_FD), VFPREG(MIPS_ARG_FS), VFPREG(MIPS_ARG_FT));
            }
        } break;
        case OL_VT_VS_IMM: {
                out = String::Format("%s $%s, $%s, %s", inst->mnemonic, COP2REG(MIPS_ARG_FT), COP2REG(MIPS_ARG_FS), _immediate((u16)inst->args[MIPS_ARG_SHAMT].value).Cstr());
        } break;
        case OL_ACC_VS_VT: {
            String name = inst->mnemonic;
            String mask = _getMask(inst);

            if (name.EndsWith("q")) {
                out = String::Format("%s $ACC, $%s, $Q", mask.Cstr(), VFPREG(MIPS_ARG_FS));
            }
            else if (name.EndsWith("i")) {
                out = String::Format("%s $ACC, $%s, $I", mask.Cstr(), VFPREG(MIPS_ARG_FS));
            }
            else if (name.EndsWith("x") || name.EndsWith("y") ||
                name.EndsWith("z") || name.EndsWith("w")) {
                const char* comp = "xyzw";
            out = String::Format("%s $ACC, $%s, $%s%c", mask.Cstr(),
                                 VFPREG(MIPS_ARG_FS), VFPREG(MIPS_ARG_FT),
                                 comp[inst->args[MIPS_ARG_FUNCT].value & 3]);
                }
            else {
                out = String::Format("%s $ACC, $%s, $%s", mask.Cstr(),
                                     VFPREG(MIPS_ARG_FS), VFPREG(MIPS_ARG_FT));
            }
        } break;
        case OL_Q_VTF: {
            const char* comp = "xyzw";
            s32 ftf = (inst->args[MIPS_ARG_RS].value >> 2) & 0b11;
            out = String::Format("%s $Q, $%s%c", inst->mnemonic, VFPREG(MIPS_ARG_FT), comp[ftf]);
        } break;
        case OL_Q_VSF_VTF: {
            const char* comp = "xyzw";
            s32 fsf = inst->args[MIPS_ARG_RS].value & 0b11;
            s32 ftf = (inst->args[MIPS_ARG_RS].value >> 2) & 0b11;
            out = String::Format("%s $Q, $%s%c, $%s%c", inst->mnemonic, VFPREG(MIPS_ARG_FS), comp[fsf],
                                 VFPREG(MIPS_ARG_FT), comp[ftf]);
        } break;
        case OL_R_VSF: {
            const char* comp = "xyzw";
            s32 fsf = inst->args[MIPS_ARG_RS].value & 0b11;
            out = String::Format("%s $R, $%s%c", inst->mnemonic, VFPREG(MIPS_ARG_FS), comp[fsf]);
        } break;
        case OL_VT_R: {
            out = String::Format("%s $%s, $R", _getMask(inst).Cstr(), VFPREG(MIPS_ARG_RT));
        } break;
        case OL_VI27: { // Only used for vcallmsr
            out = String::Format("%s %s", inst->mnemonic, g_MipsRegistersCOP2[27]);
        } break;
        case OL_HINT: {
            out = String::Format("%s %d, %s($%s)", inst->mnemonic,
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
                out = String::Format("%s 0x%02x", inst->mnemonic, stype);
            }
        } break;

        default: {
            out = "";
        } break;
    }

    return out;
}
