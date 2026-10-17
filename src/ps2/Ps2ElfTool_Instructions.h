#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "../Ps2ElfTool_Common.h"

/*
R-Type (Register)
31         26 25     21 20     16 15     11 10      6 5        0
+------------+---------+---------+---------+---------+----------+
|   opcode   |   rs    |   rt    |   rd    |  shamt  |  funct   |
|   (6 bits) | (5 bits)| (5 bits)| (5 bits)| (5 bits)| (6 bits) |
+------------+---------+---------+---------+---------+----------+

I-Type (Immediate / Memory / Branch)
31        26 25     21 20     16 15                        0
+------------+---------+---------+--------------------------+
|   opcode   |   rs    |   rt    |        immediate         |
|   (6 bits) | (5 bits)| (5 bits)|        (16 bits)         |
+------------+---------+---------+--------------------------+

J-Type (Jump)
31        26 25                                            0
+------------+----------------------------------------------+
|   opcode   |                    target                    |
|   (6 bits) |                  (26 bits)                   |
+------------+----------------------------------------------+
*/

#define MIPS_MAXARGS 8

#define MIPS_ARG_RS 0
#define MIPS_ARG_TARGET 0
#define MIPS_ARG_RT 1
#define MIPS_ARG_RD 2
#define MIPS_ARG_IMM 2
#define MIPS_ARG_SHAMT 3
#define MIPS_ARG_FUNCT 4

// For COP instructions, there is a remapping
//    rs -> fmt
//    rt -> ft
//    rd -> fs
// shamt -> fd
#define MIPS_ARG_FMT MIPS_ARG_RS
#define MIPS_ARG_FT MIPS_ARG_RT
#define MIPS_ARG_FS MIPS_ARG_RD
#define MIPS_ARG_FD MIPS_ARG_SHAMT

typedef enum oplayout {
    OL_NONE,        // nop
    OL_CALL,        // syscall, break
    OL_RD,          // mflo   $rd
    OL_RS,          // jr     $rs
    OL_RD_RS,       // jalr   $rd, $rs
    OL_RS_RT,       // div    $rs, $rt
    OL_RD_RT,       // pext5  $rd, $rt
    OL_RT_RD,       // mfc0   $rt, $rd
    OL_RD_RT_SA,    // srl    $rd, $rt, SHAMT
    OL_RD_RT_RS,    // srlv   $rd, $rt, $rs
    OL_RD_RS_RT,    // and    $rd, $rs, $rt
    OL_TARGET,      // jal    TARGET
    OL_RT_RS_IMM,   // addiu  $rt, $rs, IMM
    OL_RS_RT_IMM,   // beq    $rs, $rt, IMM
    OL_RS_IMM,      // blez   $rs, IMM
    OL_RT_IMM,      // lui    $rt, IMM
    OL_RT_OFFSET,   // lw     $rt, IMM($rs)
    OL_RT_VD,       // qmtc2  $rt, $vf_rd
    OL_VT_OFFSET,   // lqc2   $vft, IMM($rs)
    OL_VD_VS_VT,    // vadd   $vfd, $vfs, $vft
    OL_VI27,        // vcallmsr
    OL_VT_VS_IMM,   // viaddi $vif, $vis, imm5
    OL_ACC_VS_VT,   // vaddax ACC, $vfs, $vft
    OL_VT_VS,       // vitof0 $vft, $vfs
    OL_VIT_VSF,     // vmtir  $vit, $vfs<fsf>
    OL_Q_VTF,       // vsqrt  Q, $vft<ftf>
    OL_Q_VSF_VTF,   // vdiv,  Q, $vfs<fsf>, $vft<ftf>
    OL_R_VSF,       // vrinit R, $vfs<fsf>
    OL_VT_R,        // vrnext R, $vft
    OL_VS_VIT_INC,  // vsqi   $vfs, ($vit++)
    OL_VS_VIT_DEC,  // vsqi   $vfs, (--$vit)
    OL_VT_VIS_INC,  // vlqi   $vft, ($vis++)
    OL_VT_VIS_DEC,  // vlqi   $vft, (--$vis)
    OL_RT_FS,       // mfc1   $rt, $fs
    OL_FT_OFFSET,   // lwc1   $ft, IMM($rs)
    OL_FD_FS_FT,    // add.s  $fd, $fs, $ft
    OL_FD_FS,       // abs.s  $fd, $fs
    OL_FS_FT,       // c.lt.s $fs, $ft
    OL_FD_FT,       // sqrt.s $fd, $ft
    OL_HINT,        // pref   hint, IMM($rs)
    OL_SYNC         // sync
} MipsOpLayout;

typedef enum insttype : s32 {
    ITYPE_INVALID = -1,
    ITYPE_NOP,
    ITYPE_R,
    ITYPE_I,
    ITYPE_J
} MipsInstType;

typedef enum argtype {
    AT_NULL,
    AT_RS,
    AT_RT,
    AT_RD,
    AT_SHAMT,
    AT_FUNCT,
    AT_IMMEDIATE,
    AT_TARGET
} MipsArgType;

typedef struct mipsarg {
    MipsArgType type;
    u8 bits;
    u32 value;
} MipsArgument;

#define ARG_RS { AT_RS, 5, 0 }
#define ARG_RT { AT_RT, 5, 0 }
#define ARG_RD { AT_RD, 5, 0 }
#define ARG_SHAMT { AT_SHAMT, 5, 0 }
#define ARG_FUNCT(code) { AT_FUNCT, 6, code }
#define ARG_IMMEDIATE { AT_IMMEDIATE, 16, 0 }
#define ARG_TARGET { AT_TARGET, 26, 0 }

#define ARG_FMT(code) { AT_RS, 5, code }
#define ARG_FT(code) { AT_RT, 5, code }

typedef struct mipsinst {
    const char* mnemonic;
    u8 opcode;
    MipsInstType type;
    MipsOpLayout layout;
    MipsArgument args[MIPS_MAXARGS];
} MipsInstruction;

// MMI
#define InstMMIType(mnemonic, layout, funct) { mnemonic, 0x1c, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(funct) } }
#define InstMMI0Type(mnemonic, layout, shamt) { mnemonic, 0x1c, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, {AT_SHAMT, 5, shamt}, ARG_FUNCT(0b001000) } }
#define InstMMI1Type(mnemonic, layout, shamt) { mnemonic, 0x1c, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, {AT_SHAMT, 5, shamt}, ARG_FUNCT(0b101000) } }
#define InstMMI2Type(mnemonic, layout, shamt) { mnemonic, 0x1c, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, {AT_SHAMT, 5, shamt}, ARG_FUNCT(0b001001) } }
#define InstMMI3Type(mnemonic, layout, shamt) { mnemonic, 0x1c, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, {AT_SHAMT, 5, shamt}, ARG_FUNCT(0b101001) } }
#define InstREGIMMType(mnemonic, layout, rt) { mnemonic, 0x1, ITYPE_I, layout, { ARG_RS, { AT_RT, 5, rt }, ARG_IMMEDIATE } }

// COP0 & TLB
#define InstCOP0Type(mnemonic, layout, rs) { mnemonic, 0x10, ITYPE_R, layout, { ARG_FMT(rs), ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(0b000000) } }
#define InstBC0Type(mnemonic, layout, rt) { mnemonic, 0x10, ITYPE_I, layout, { ARG_FMT(0b01000), ARG_FT(rt), ARG_IMMEDIATE } }
#define InstTLBType(mnemonic, layout, rt) { mnemonic, 0x10, ITYPE_I, layout, { ARG_FMT(0b10000), ARG_FT(rt), ARG_IMMEDIATE } }

// COP1 & FPU
#define InstCOP1Type(mnemonic, layout, rs) { mnemonic, 0x11, ITYPE_R, layout, { ARG_FMT(rs), ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(0b000000) } }
#define InstBC1Type(mnemonic, layout, rt) { mnemonic, 0x11, ITYPE_I, layout, { ARG_FMT(0b01000), ARG_FT(rt), ARG_IMMEDIATE } }
#define InstFPUSType(mnemonic, layout, funct) { mnemonic, 0x11, ITYPE_R, layout, { ARG_FMT(0b10000), ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(funct) } }
#define InstFPUWType(mnemonic, layout, funct) { mnemonic, 0x11, ITYPE_R, layout, { ARG_FMT(0b10100), ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(funct) } }

// COP2 & VU0 Macro
#define InstCOP2Type(mnemonic, layout, rs) { mnemonic, 0x12, ITYPE_R, layout, { ARG_FMT(rs), ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(0b000000) } }
#define InstBC2Type(mnemonic, layout, rt) { mnemonic, 0x12, ITYPE_I, layout, { ARG_FMT(0b01000), ARG_FT(rt), ARG_IMMEDIATE } }
#define InstCOP2Spec1Type(mnemonic, layout, funct) { mnemonic, 0x12, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(funct) } }
#define InstCOP2Spec2Type(mnemonic, layout, funct) { mnemonic, 0x12, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(funct) } }

// MIPS instruction types
#define InstRType(mnemonic, layout, funct) { mnemonic, 0b000000, ITYPE_R, layout, { ARG_RS, ARG_RT, ARG_RD, ARG_SHAMT, ARG_FUNCT(funct) } }
#define InstIType(mnemonic, layout, opcode) { mnemonic, opcode, ITYPE_I, layout, { ARG_RS, ARG_RT, ARG_IMMEDIATE } }
#define InstJType(mnemonic, layout, opcode) { mnemonic, opcode, ITYPE_J, layout, { ARG_TARGET } }

#define InstNop { "nop", 0b000000, ITYPE_NOP, OL_NONE, {} }

extern MipsInstruction g_MipsInstructionsR[];
extern MipsInstruction g_MipsInstructionsIJ[];
extern MipsInstruction g_MipsInstructionsMMI[];
extern MipsInstruction g_MipsInstructionsMMI0[];
extern MipsInstruction g_MipsInstructionsMMI1[];
extern MipsInstruction g_MipsInstructionsMMI2[];
extern MipsInstruction g_MipsInstructionsMMI3[];
extern MipsInstruction g_MipsInstructionsREGIMM[];
extern MipsInstruction g_MipsInstructionsCOP0[];
extern MipsInstruction g_MipsInstructionsBC0[];
extern MipsInstruction g_MipsInstructionsTLB[];
extern MipsInstruction g_MipsInstructionsCOP1[];
extern MipsInstruction g_MipsInstructionsBC1[];
extern MipsInstruction g_MipsInstructionsFPUS[];
extern MipsInstruction g_MipsInstructionsFPUW[];
extern MipsInstruction g_MipsInstructionsCOP2[];
extern MipsInstruction g_MipsInstructionsBC2[];
extern MipsInstruction g_MipsInstructionsCOP2S1[];
extern MipsInstruction g_MipsInstructionsCOP2S2[];

MipsInstruction* FindInstruction(u32 instruction);

#endif
