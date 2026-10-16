#include "Ps2ElfTool_Instructions.h"

MipsInstruction g_MipsInstructionsIJ[] = {
    InstNop, // R-Type                0b000000
    InstNop, // REGIMM                0b000001
    InstJType("j",     OL_TARGET,     0b000010),
    InstJType("jal",   OL_TARGET,     0b000011),
    InstIType("beq",   OL_RS_RT_IMM,  0b000100),
    InstIType("bne",   OL_RS_RT_IMM,  0b000101),
    InstIType("blez",  OL_RS_IMM,     0b000110),
    InstIType("bgtz",  OL_RS_IMM,     0b000111),
    InstIType("addi",  OL_RT_RS_IMM,  0b001000),
    InstIType("addiu", OL_RT_RS_IMM,  0b001001),
    InstIType("slti",  OL_RT_RS_IMM,  0b001010),
    InstIType("sltiu", OL_RT_RS_IMM,  0b001011),
    InstIType("andi",  OL_RT_RS_IMM,  0b001100),
    InstIType("ori",   OL_RT_RS_IMM,  0b001101),
    InstIType("xori",  OL_RT_RS_IMM,  0b001110),
    InstIType("lui",   OL_RT_IMM,     0b001111),
    InstNop, // COP0                  0b010000
    InstNop, // COP1                  0b010001
    InstNop, // COP2                  0b010010
    InstNop, //                       0b010011
    InstIType("beql",  OL_RS_RT_IMM,  0b010100),
    InstIType("bnel",  OL_RS_RT_IMM,  0b010101),
    InstIType("blezl", OL_RS_RT_IMM,  0b010110),
    InstIType("bgtzl", OL_RS_RT_IMM,  0b010111),
    InstIType("daddi", OL_RT_RS_IMM,  0b011000),
    InstIType("daddiu",OL_RT_RS_IMM,  0b011001),
    InstIType("ldl",   OL_RT_OFFSET,  0b011010),
    InstIType("ldr",   OL_RT_OFFSET,  0b011011),
    InstNop, // MMI                   0b011100
    InstNop, //                       0b011101
    InstIType("lq",    OL_RT_OFFSET,  0b011110),
    InstIType("sq",    OL_RT_OFFSET,  0b011111),
    InstIType("lb",    OL_RT_OFFSET,  0b100000),
    InstIType("lh",    OL_RT_OFFSET,  0b100001),
    InstIType("lwl",   OL_RT_OFFSET,  0b100010),
    InstIType("lw",    OL_RT_OFFSET,  0b100011),
    InstIType("lbu",   OL_RT_OFFSET,  0b100100),
    InstIType("lhu",   OL_RT_OFFSET,  0b100101),
    InstIType("lwr",   OL_RT_OFFSET,  0b100110),
    InstIType("lwu",   OL_RT_OFFSET,  0b100111),
    InstIType("sb",    OL_RT_OFFSET,  0b101000),
    InstIType("sh",    OL_RT_OFFSET,  0b101001),
    InstIType("swl",   OL_RT_OFFSET,  0b101010),
    InstIType("sw",    OL_RT_OFFSET,  0b101011),
    InstIType("sdl",   OL_RT_OFFSET,  0b101100),
    InstIType("sdr",   OL_RT_OFFSET,  0b101101),
    InstIType("swr",   OL_RT_OFFSET,  0b101110),
    InstIType("cache", OL_RT_OFFSET,  0b101111),
    InstNop, //                       0b110000
    InstIType("lwc1",  OL_FT_OFFSET,  0b110001),
    InstNop, //                       0b110010
    InstIType("pref",  OL_HINT,       0b110011),
    InstNop, //                       0b110100
    InstNop, //                       0b110101
    InstIType("lqc2",  OL_VT_OFFSET,  0b110110),
    InstIType("ld",    OL_RT_OFFSET,  0b110111),
    InstNop, //                       0b111000
    InstIType("swc1",  OL_FT_OFFSET,  0b111001),
    InstNop, //                       0b111010
    InstNop, //                       0b111011
    InstNop, //                       0b111100
    InstNop, //                       0b111101
    InstIType("sqc2",  OL_VT_OFFSET,  0b111110),
    InstIType("sd",    OL_RT_OFFSET,  0b111111),
};

MipsInstruction g_MipsInstructionsR[] = {
    InstRType("sll",     OL_RD_RT_SA, 0b000000),
    InstNop, //                       0b000001
    InstRType("srl",     OL_RD_RT_SA, 0b000010),
    InstRType("sra",     OL_RD_RT_SA, 0b000011),
    InstRType("sllv",    OL_RD_RT_RS, 0b000100),
    InstNop, //                       0b110101
    InstRType("srlv",    OL_RD_RT_RS, 0b000110),
    InstRType("srav",    OL_RD_RT_RS, 0b000111),
    InstRType("jr",      OL_RS,       0b001000),
    InstRType("jalr",    OL_RD_RS,    0b001001),
    InstRType("movz",    OL_RD_RS_RT, 0b001010),
    InstRType("movn",    OL_RD_RS_RT, 0b001011),
    InstRType("syscall", OL_NONE,     0b001100),
    InstRType("break",   OL_NONE,     0b001101),
    InstNop, //                       0b001110
    InstRType("sync",    OL_SYNC,     0b001111),
    InstRType("mfhi",    OL_RD,       0b010000),
    InstRType("mthi",    OL_RS,       0b010001),
    InstRType("mflo",    OL_RD,       0b010010),
    InstRType("mtlo",    OL_RS,       0b010011),
    InstRType("dsllv",   OL_RD_RS_RT, 0b010100),
    InstNop, //                       0b010101
    InstRType("dsrlv",   OL_RD_RT_RS, 0b010110),
    InstRType("dsrav",   OL_RD_RT_RS, 0b010111),
    InstRType("mult",    OL_RD_RS_RT, 0b011000),
    InstRType("multu",   OL_RD_RS_RT, 0b011001),
    InstRType("div",     OL_RS_RT,    0b011010),
    InstRType("divu",    OL_RS_RT,    0b011011),
    InstNop, //                       0b011100
    InstNop, //                       0b011101
    InstNop, //                       0b011110
    InstNop, //                       0b011111
    InstRType("add",     OL_RD_RS_RT, 0b100000),
    InstRType("addu",    OL_RD_RS_RT, 0b100001),
    InstRType("sub",     OL_RD_RS_RT, 0b100010),
    InstRType("subu",    OL_RD_RS_RT, 0b100011),
    InstRType("and",     OL_RD_RS_RT, 0b100100),
    InstRType("or",      OL_RD_RS_RT, 0b100101),
    InstRType("xor",     OL_RD_RS_RT, 0b100110),
    InstRType("nor",     OL_RD_RS_RT, 0b100111),
    InstRType("mfsa",    OL_RD,       0b101000),
    InstRType("mtsa",    OL_RS,       0b101001),
    InstRType("slt",     OL_RD_RS_RT, 0b101010),
    InstRType("sltu",    OL_RD_RS_RT, 0b101011),
    InstRType("dadd",    OL_RD_RS_RT, 0b101100),
    InstRType("daddu",   OL_RD_RS_RT, 0b101101),
    InstRType("dsub",    OL_RD_RS_RT, 0b101110),
    InstRType("dsubu",   OL_RD_RS_RT, 0b101111),
    InstRType("tge",     OL_RS_RT,    0b110000),
    InstRType("tgeu",    OL_RS_RT,    0b110001),
    InstRType("tlt",     OL_RS_RT,    0b110010),
    InstRType("tltu",    OL_RS_RT,    0b110011),
    InstRType("teq",     OL_RS_RT,    0b110100),
    InstNop, //                       0b110101
    InstRType("tne",     OL_RS_RT,    0b110110),
    InstNop, //                       0b110111
    InstRType("dsll",    OL_RD_RT_SA, 0b111000),
    InstNop, //                       0b111001
    InstRType("dsrl",    OL_RD_RT_SA, 0b111010),
    InstRType("dsra",    OL_RD_RT_SA, 0b111011),
    InstRType("dsll32",  OL_RD_RT_SA, 0b111100),
    InstNop, //                       0b111101
    InstRType("dsrl32",  OL_RD_RT_SA, 0b111110),
    InstRType("dsra32",  OL_RD_RT_SA, 0b111111),
};

MipsInstruction g_MipsInstructionsMMI[] = {
    InstMMIType("madd",   OL_RS_RT,    0b000000),
    InstMMIType("maddu",  OL_RS_RT,    0b000001),
    InstNop, //                        0b000010
    InstNop, //                        0b000011
    InstMMIType("plzcw",  OL_RD_RS,    0b000100),
    InstNop, //                        0b000101
    InstNop, //                        0b000110
    InstNop, //                        0b000111
    InstNop, // MMI0                   0b001000
    InstNop, // MMI2                   0b001001
    InstNop, //                        0b001010
    InstNop, //                        0b001011
    InstNop, //                        0b001100
    InstNop, //                        0b001101
    InstNop, //                        0b001110
    InstNop, //                        0b001111
    InstMMIType("mfhi1",  OL_RD,       0b010000),
    InstMMIType("mthi1",  OL_RS,       0b010001),
    InstMMIType("mflo1",  OL_RD,       0b010010),
    InstMMIType("mtlo1",  OL_RS,       0b010011),
    InstNop, //                        0b010100,
    InstNop, //                        0b010101,
    InstNop, //                        0b010110
    InstNop, //                        0b010111
    InstMMIType("mult1",  OL_RD_RS_RT, 0b011000),
    InstMMIType("multu1", OL_RD_RS_RT, 0b011001),
    InstMMIType("div1",   OL_RD_RS_RT, 0b011010),
    InstMMIType("divu1",  OL_RD_RS_RT, 0b011011),
    InstNop, //                        0b011100
    InstNop, //                        0b011101
    InstNop, //                        0b011110
    InstNop, //                        0b011111
    InstMMIType("madd1",  OL_RD_RS_RT, 0b100000),
    InstMMIType("maddu1", OL_RD_RS_RT, 0b100001),
    InstNop, //                        0b100010
    InstNop, //                        0b100011
    InstNop, //                        0b100100
    InstNop, //                        0b100101
    InstNop, //                        0b100110
    InstNop, //                        0b100111
    InstNop, // MMI1                   0b101000
    InstNop, // MMI3                   0b101001
    InstNop, //                        0b101010
    InstNop, //                        0b101011
    InstNop, //                        0b101100
    InstNop, //                        0b101101
    InstNop, //                        0b101110
    InstNop, //                        0b101111
    InstMMIType("pmfhl",  OL_RD,       0b110000),
    InstMMIType("pmthl",  OL_RS,       0b110001),
    InstNop, //                        0b110010
    InstNop, //                        0b110011
    InstMMIType("psllh",  OL_RD_RT_SA, 0b110100),
    InstNop, //                        0b110101
    InstMMIType("psrlh",  OL_RD_RT_SA, 0b110110),
    InstMMIType("psrah",  OL_RD_RT_SA, 0b110111),
    InstNop, //                        0b111000
    InstNop, //                        0b111001
    InstNop, //                        0b111010
    InstNop, //                        0b111011
    InstMMIType("psllw",  OL_RD_RT_SA, 0b111100),
    InstNop, //                        0b111101
    InstMMIType("psrlw",  OL_RD_RT_SA, 0b111110),
    InstMMIType("psraw",  OL_RD_RT_SA, 0b111111)
};

MipsInstruction g_MipsInstructionsMMI0[] = {
    InstMMI0Type("paddw",  OL_RD_RS_RT, 0b00000),
    InstMMI0Type("psubw",  OL_RD_RS_RT, 0b00001),
    InstMMI0Type("pcgtw",  OL_RD_RS_RT, 0b00010),
    InstMMI0Type("pmaxw",  OL_RD_RS_RT, 0b00011),
    InstMMI0Type("paddh",  OL_RD_RS_RT, 0b00100),
    InstMMI0Type("psubh",  OL_RD_RS_RT, 0b00101),
    InstMMI0Type("pcgth",  OL_RD_RS_RT, 0b00110),
    InstMMI0Type("pmaxh",  OL_RD_RS_RT, 0b00111),
    InstMMI0Type("paddb",  OL_RD_RS_RT, 0b01000),
    InstMMI0Type("psubb",  OL_RD_RS_RT, 0b01001),
    InstMMI0Type("pcgtb",  OL_RD_RS_RT, 0b01010),
    InstNop, //                         0b01011
    InstNop, //                         0b01100
    InstNop, //                         0b01101
    InstNop, //                         0b01110
    InstNop, //                         0b01111
    InstMMI0Type("paddsw", OL_RD_RS_RT, 0b10000),
    InstMMI0Type("psubsw", OL_RD_RS_RT, 0b10001),
    InstMMI0Type("pextlw", OL_RD_RS_RT, 0b10010),
    InstMMI0Type("ppacw",  OL_RD_RS_RT, 0b10011),
    InstMMI0Type("paddsh", OL_RD_RS_RT, 0b10100),
    InstMMI0Type("psubsh", OL_RD_RS_RT, 0b10101),
    InstMMI0Type("pextlh", OL_RD_RS_RT, 0b10110),
    InstMMI0Type("ppach",  OL_RD_RS_RT, 0b10111),
    InstMMI0Type("paddsb", OL_RD_RS_RT, 0b11000),
    InstMMI0Type("psubsb", OL_RD_RS_RT, 0b11001),
    InstMMI0Type("pextlb", OL_RD_RS_RT, 0b11010),
    InstMMI0Type("ppacb",  OL_RD_RS_RT, 0b11011),
    InstNop, //                         0b11100
    InstNop, //                         0b11101
    InstMMI0Type("pext5",  OL_RD_RT,    0b11110),
    InstMMI0Type("ppac5",  OL_RD_RT,    0b11111)
};

MipsInstruction g_MipsInstructionsMMI1[] = {
    InstNop, //                         0b00000
    InstMMI1Type("pabsw",  OL_RD_RT,    0b00001),
    InstMMI1Type("pceqw",  OL_RD_RS_RT, 0b00010),
    InstMMI1Type("pminw",  OL_RD_RS_RT, 0b00011),
    InstMMI1Type("padsbh", OL_RD_RS_RT, 0b00100),
    InstMMI1Type("pabsh",  OL_RD_RT,    0b00101),
    InstMMI1Type("pceqh",  OL_RD_RS_RT, 0b00110),
    InstMMI1Type("pminh",  OL_RD_RS_RT, 0b00111),
    InstNop, //                         0b01000
    InstNop, //                         0b01001
    InstMMI1Type("pceqb",  OL_RD_RS_RT, 0b01010),
    InstNop, //                         0b01011
    InstNop, //                         0b01100
    InstNop, //                         0b01101
    InstNop, //                         0b01110
    InstNop, //                         0b01111
    InstMMI1Type("padduw", OL_RD_RS_RT, 0b10000),
    InstMMI1Type("psubuw", OL_RD_RS_RT, 0b10001),
    InstMMI1Type("pextuw", OL_RD_RS_RT, 0b10010),
    InstNop, //                         0b10111
    InstMMI1Type("padduh", OL_RD_RS_RT, 0b10100),
    InstMMI1Type("psubuh", OL_RD_RS_RT, 0b10101),
    InstMMI1Type("pextuh", OL_RD_RS_RT, 0b10110),
    InstNop, //                         0b10111
    InstMMI1Type("paddub", OL_RD_RS_RT, 0b11000),
    InstMMI1Type("psubub", OL_RD_RS_RT, 0b11001),
    InstMMI1Type("pextub", OL_RD_RS_RT, 0b11010),
    InstMMI1Type("qfsrv",  OL_RD_RS_RT, 0b11011),
    InstNop, //                         0b11100
    InstNop, //                         0b11101
    InstNop, //                         0b11110
    InstNop, //                         0b11111
};

MipsInstruction g_MipsInstructionsMMI2[] = {
    InstMMI2Type("pmaddw",  OL_RD_RS_RT, 0b00000),
    InstNop, //                          0b00001
    InstMMI2Type("psllvw",  OL_RD_RT_RS, 0b00010),
    InstMMI2Type("psrlvw",  OL_RD_RT_RS, 0b00011),
    InstMMI2Type("pmsubw",  OL_RD_RS_RT, 0b00100),
    InstNop, //                          0b00101
    InstNop, //                          0b00110
    InstNop, //                          0b00111
    InstMMI2Type("pmfhi",   OL_RD,       0b01000),
    InstMMI2Type("pmflo",   OL_RS,       0b01001),
    InstMMI2Type("pinth",   OL_RD_RS_RT, 0b01010),
    InstNop, //                          0b01011
    InstMMI2Type("pmultw",  OL_RD_RS_RT, 0b01100),
    InstMMI2Type("pdivw",   OL_RS_RT,    0b01101),
    InstMMI2Type("pcpyld",  OL_RD_RS_RT, 0b01110),
    InstNop, //                          0b01111
    InstMMI2Type("pmaddh",  OL_RD_RS_RT, 0b10000),
    InstMMI2Type("phmadh",  OL_RD_RS_RT, 0b10001),
    InstMMI2Type("pand",    OL_RD_RS_RT, 0b10010),
    InstMMI2Type("pxor",    OL_RD_RS_RT, 0b10011),
    InstMMI2Type("pmsubh",  OL_RD_RS_RT, 0b10100),
    InstMMI2Type("phmsbh",  OL_RD_RS_RT, 0b10101),
    InstNop, //                          0b10110
    InstNop, //                          0b10111
    InstNop, //                          0b11000
    InstNop, //                          0b11001
    InstMMI2Type("pexeh",   OL_RD_RT,    0b11010),
    InstMMI2Type("prevh",   OL_RD_RT,    0b11011),
    InstMMI2Type("pmulth",  OL_RD_RS_RT, 0b11100),
    InstMMI2Type("pdivbw",  OL_RS_RT,    0b11101),
    InstMMI2Type("pexew",   OL_RD_RT,    0b11110),
    InstMMI2Type("prot3w",  OL_RD_RT,    0b11111)
};

MipsInstruction g_MipsInstructionsMMI3[] = {
    InstMMI3Type("pmadduw", OL_RD_RS_RT, 0b00000),
    InstNop, //                          0b00001
    InstNop, //                          0b00010
    InstMMI3Type("psravw",  OL_RD_RT_RS, 0b00011),
    InstNop, //                          0b00100
    InstNop, //                          0b00101
    InstNop, //                          0b00110
    InstNop, //                          0b00111
    InstMMI3Type("pmthi",   OL_RS,       0b01000),
    InstMMI3Type("pmtlo",   OL_RS,       0b01001),
    InstMMI3Type("pinteh",  OL_RD_RS_RT, 0b01010),
    InstNop, //                          0b01011
    InstMMI3Type("pmultuw", OL_RD_RS_RT, 0b01100),
    InstMMI3Type("pdivuw",  OL_RS_RT,    0b01101),
    InstMMI3Type("pcpyud",  OL_RD_RS_RT, 0b01110),
    InstNop, //                          0b01111
    InstNop, //                          0b10000
    InstNop, //                          0b10001
    InstMMI3Type("por",     OL_RD_RS_RT, 0b10010),
    InstMMI3Type("pnor",    OL_RD_RS_RT, 0b10011),
    InstNop, //                          0b10100
    InstNop, //                          0b10101
    InstNop, //                          0b10110
    InstNop, //                          0b10111
    InstNop, //                          0b11000
    InstNop, //                          0b11001
    InstMMI3Type("pexch",   OL_RD_RT,    0b11010),
    InstMMI3Type("pcpyh",   OL_RD_RT,    0b11011),
    InstNop, //                          0b11100
    InstNop, //                          0b11101
    InstMMI3Type("pexcw",   OL_RD_RT,    0b11110),
    InstNop, //                          0b11111
};

MipsInstruction g_MipsInstructionsREGIMM[] = {
    InstREGIMMType("bltz",    OL_RS_IMM, 0b00000),
    InstREGIMMType("bgez",    OL_RS_IMM, 0b00001),
    InstREGIMMType("bltzl",   OL_RS_IMM, 0b00010),
    InstREGIMMType("bgezl",   OL_RS_IMM, 0b00011),
    InstNop, //                          0b00100
    InstNop, //                          0b00101
    InstNop, //                          0b00110
    InstNop, //                          0b00111
    InstREGIMMType("tgei",    OL_RS_IMM, 0b01000),
    InstREGIMMType("tgeiu",   OL_RS_IMM, 0b01001),
    InstREGIMMType("tlti",    OL_RS_IMM, 0b01010),
    InstREGIMMType("tltiu",   OL_RS_IMM, 0b01011),
    InstREGIMMType("teqi",    OL_RS_IMM, 0b01100),
    InstNop, //                          0b01101
    InstREGIMMType("tnei",    OL_RS_IMM, 0b01110),
    InstNop, //                          0b01111
    InstREGIMMType("bltzal",  OL_RS_IMM, 0b10000),
    InstREGIMMType("bgezal",  OL_RS_IMM, 0b10001),
    InstREGIMMType("bltzall", OL_RS_IMM, 0b10010),
    InstREGIMMType("bgezall", OL_RS_IMM, 0b10011),
    InstNop, //                          0b10100
    InstNop, //                          0b10101
    InstNop, //                          0b10110
    InstNop, //                          0b10111
    InstREGIMMType("mtsab",   OL_RS_IMM, 0b11000),
    InstREGIMMType("mtsah",   OL_RS_IMM, 0b11001),
    InstNop, //                          0b11010
    InstNop, //                          0b11011
    InstNop, //                          0b11100
    InstNop, //                          0b11101
    InstNop, //                          0b11110
    InstNop, //                          0b11111
};

MipsInstruction g_MipsInstructionsCOP0[] = {
    InstCOP0Type("mfc0", OL_RT_RD, 0b00000),
    InstNop, //                    0b00001
    InstNop, //                    0b00010
    InstNop, //                    0b00011
    InstCOP0Type("mtc0", OL_RT_RD, 0b00100),
    InstNop, //                    0b00101
    InstNop, //                    0b00110
    InstNop, //                    0b00111
    InstNop, // BC0                0b01000
    InstNop, //                    0b01001
    InstNop, //                    0b01010
    InstNop, //                    0b01011
    InstNop, //                    0b01100
    InstNop, //                    0b01101
    InstNop, //                    0b01110
    InstNop, //                    0b01111
    InstNop, // TLB                0b10000
    InstNop, //                    0b10001
    InstNop, //                    0b10010
    InstNop, //                    0b10011
    InstNop, //                    0b10100
    InstNop, //                    0b10101
    InstNop, //                    0b10110
    InstNop, //                    0b10111
    InstNop, //                    0b11000
    InstNop, //                    0b11001
    InstNop, //                    0b11010
    InstNop, //                    0b11011
    InstNop, //                    0b11100
    InstNop, //                    0b11101
    InstNop, //                    0b11110
    InstNop, //                    0b11111
};

MipsInstruction g_MipsInstructionsBC0[] = {
    InstBC0Type("bc0f",  OL_TARGET, 0b00000),
    InstBC0Type("bc0t",  OL_TARGET, 0b00001),
    InstBC0Type("bc0fl", OL_TARGET, 0b00010),
    InstBC0Type("bc0tl", OL_TARGET, 0b00011),
    InstNop, //                     0b00100
    InstNop, //                     0b00101
    InstNop, //                     0b00110
    InstNop, //                     0b00111
    InstNop, //                     0b01000
    InstNop, //                     0b01001
    InstNop, //                     0b01010
    InstNop, //                     0b01011
    InstNop, //                     0b01100
    InstNop, //                     0b01101
    InstNop, //                     0b01110
    InstNop, //                     0b01111
    InstNop, //                     0b10000
    InstNop, //                     0b10001
    InstNop, //                     0b10010
    InstNop, //                     0b10011
    InstNop, //                     0b10100
    InstNop, //                     0b10101
    InstNop, //                     0b10110
    InstNop, //                     0b10111
    InstNop, //                     0b11000
    InstNop, //                     0b11001
    InstNop, //                     0b11010
    InstNop, //                     0b11011
    InstNop, //                     0b11100
    InstNop, //                     0b11101
    InstNop, //                     0b11110
    InstNop, //                     0b11111
};

MipsInstruction g_MipsInstructionsTLB[] = {
    InstNop, //                   0b000000
    InstTLBType("tlbr",  OL_NONE, 0b000001),
    InstTLBType("tlbwi", OL_NONE, 0b000010),
    InstNop, //                   0b000011
    InstNop, //                   0b000100
    InstNop, //                   0b000101
    InstTLBType("tlbwr", OL_NONE, 0b000110),
    InstNop, //                   0b000111
    InstTLBType("tlbp",  OL_NONE, 0b001000),
    InstNop, //                   0b001001
    InstNop, //                   0b001010
    InstNop, //                   0b001011
    InstNop, //                   0b001100
    InstNop, //                   0b001101
    InstNop, //                   0b001110
    InstNop, //                   0b001111
    InstNop, //                   0b010000
    InstNop, //                   0b010001
    InstNop, //                   0b010010
    InstNop, //                   0b010011
    InstNop, //                   0b010100
    InstNop, //                   0b010101
    InstNop, //                   0b010110
    InstNop, //                   0b010111
    InstTLBType("eret",  OL_NONE, 0b011000),
    InstNop, //                   0b011001
    InstNop, //                   0b011010
    InstNop, //                   0b011011
    InstNop, //                   0b011100
    InstNop, //                   0b011101
    InstNop, //                   0b011110
    InstNop, //                   0b011111
    InstNop, //                   0b100000
    InstNop, //                   0b100001
    InstNop, //                   0b100010
    InstNop, //                   0b100011
    InstNop, //                   0b100100
    InstNop, //                   0b100101
    InstNop, //                   0b100110
    InstNop, //                   0b100111
    InstNop, //                   0b101000
    InstNop, //                   0b101001
    InstNop, //                   0b101010
    InstNop, //                   0b101011
    InstNop, //                   0b101100
    InstNop, //                   0b101101
    InstNop, //                   0b101110
    InstNop, //                   0b101111
    InstNop, //                   0b110000
    InstNop, //                   0b110001
    InstNop, //                   0b110010
    InstNop, //                   0b110011
    InstNop, //                   0b110100
    InstNop, //                   0b110101
    InstNop, //                   0b110110
    InstNop, //                   0b110111
    InstTLBType("ei",    OL_NONE, 0b111000),
    InstTLBType("di",    OL_NONE, 0b111001),
    InstNop, //                   0b111010
    InstNop, //                   0b111011
    InstNop, //                   0b111100
    InstNop, //                   0b111101
    InstNop, //                   0b111110
    InstNop, //                   0b111111
};

MipsInstruction g_MipsInstructionsCOP1[] = {
    InstCOP1Type("mfc1", OL_RT_FS, 0b00000),
    InstNop, //                    0b00001
    InstCOP1Type("cfc1", OL_RT_FS, 0b00010),
    InstNop, //                    0b00011
    InstCOP1Type("mtc1", OL_RT_FS, 0b00100),
    InstNop, //                    0b00101
    InstCOP1Type("ctc1", OL_RT_FS, 0b00110),
    InstNop, //                    0b00111
    InstNop, // BC1                0b01000
    InstNop, //                    0b01001
    InstNop, //                    0b01010
    InstNop, //                    0b01011
    InstNop, //                    0b01100
    InstNop, //                    0b01101
    InstNop, //                    0b01110
    InstNop, //                    0b01111
    InstNop, // FPU.S              0b10000
    InstNop, //                    0b10001
    InstNop, //                    0b10010
    InstNop, //                    0b10011
    InstNop, // FPU.W              0b10100
    InstNop, //                    0b10101
    InstNop, //                    0b10110
    InstNop, //                    0b10111
    InstNop, //                    0b11000
    InstNop, //                    0b11001
    InstNop, //                    0b11010
    InstNop, //                    0b11011
    InstNop, //                    0b11100
    InstNop, //                    0b11101
    InstNop, //                    0b11110
    InstNop, //                    0b11111
};

MipsInstruction g_MipsInstructionsBC1[] = {
    InstBC1Type("bc1f",  OL_TARGET, 0b00000),
    InstBC1Type("bc1t",  OL_TARGET, 0b00001),
    InstBC1Type("bc1fl", OL_TARGET, 0b00010),
    InstBC1Type("bc1tl", OL_TARGET, 0b00011),
    InstNop, //                     0b00100
    InstNop, //                     0b00101
    InstNop, //                     0b00110
    InstNop, //                     0b00111
    InstNop, //                     0b01000
    InstNop, //                     0b01001
    InstNop, //                     0b01010
    InstNop, //                     0b01011
    InstNop, //                     0b01100
    InstNop, //                     0b01101
    InstNop, //                     0b01110
    InstNop, //                     0b01111
    InstNop, //                     0b10000
    InstNop, //                     0b10001
    InstNop, //                     0b10010
    InstNop, //                     0b10011
    InstNop, //                     0b10100
    InstNop, //                     0b10101
    InstNop, //                     0b10110
    InstNop, //                     0b10111
    InstNop, //                     0b11000
    InstNop, //                     0b11001
    InstNop, //                     0b11010
    InstNop, //                     0b11011
    InstNop, //                     0b11100
    InstNop, //                     0b11101
    InstNop, //                     0b11110
    InstNop, //                     0b11111
};

MipsInstruction g_MipsInstructionsFPUS[] = {
    InstFPUSType("add.s",   OL_FD_FS_FT, 0b000000),
    InstFPUSType("sub.s",   OL_FD_FS_FT, 0b000001),
    InstFPUSType("mul.s",   OL_FD_FS_FT, 0b000010),
    InstFPUSType("div.s",   OL_FD_FS_FT, 0b000011),
    InstFPUSType("sqrt.s",  OL_FD_FT,    0b000100),
    InstFPUSType("abs.s",   OL_FD_FS,    0b000101),
    InstFPUSType("mov.s",   OL_FD_FS,    0b000110),
    InstFPUSType("neg.s",   OL_FD_FS,    0b000111),
    InstNop, //                          0b001000
    InstNop, //                          0b001001
    InstNop, //                          0b001010
    InstNop, //                          0b001011
    InstNop, //                          0b001100
    InstNop, //                          0b001101
    InstNop, //                          0b001110
    InstNop, //                          0b001111
    InstNop, //                          0b010000
    InstNop, //                          0b010001
    InstNop, //                          0b010010
    InstNop, //                          0b010011
    InstNop, //                          0b010100
    InstNop, //                          0b010101
    InstFPUSType("rsqrt.s", OL_FD_FS_FT, 0b010110),
    InstNop, //                          0b010111
    InstFPUSType("adda.s",  OL_FS_FT,    0b011000),
    InstFPUSType("suba.s",  OL_FS_FT,    0b011001),
    InstFPUSType("mula.s",  OL_FS_FT,    0b011010),
    InstNop, //                          0b011011
    InstFPUSType("madd.s",  OL_FD_FS_FT, 0b011100),
    InstFPUSType("msub.s",  OL_FD_FS_FT, 0b011101),
    InstFPUSType("madda.s", OL_FS_FT,    0b011110),
    InstFPUSType("msuba.s", OL_FS_FT,    0b011111),
    InstNop, //                          0b100000
    InstNop, //                          0b100001
    InstNop, //                          0b100010
    InstNop, //                          0b100011
    InstFPUSType("cvt.w.s",   OL_FD_FS,  0b100100),
    InstNop, //                          0b100101
    InstNop, //                          0b100110
    InstNop, //                          0b100111
    InstFPUSType("max.s",   OL_FD_FS_FT, 0b101000),
    InstFPUSType("min.s",   OL_FD_FS_FT, 0b101001),
    InstNop, //                          0b101010
    InstNop, //                          0b101011
    InstNop, //                          0b101100
    InstNop, //                          0b101101
    InstNop, //                          0b101110
    InstNop, //                          0b101111
    InstFPUSType("c.f.s",     OL_FS_FT,  0b110000),
    InstNop, //                          0b110001
    InstFPUSType("c.eq.s",    OL_FS_FT,  0b110010),
    InstNop, //                          0b110011
    InstFPUSType("c.lt.s",    OL_FS_FT,  0b110100),
    InstNop, //                          0b100101
    InstFPUSType("c.le.s",    OL_FS_FT,  0b110110),
    InstNop, //                          0b110111
    InstNop, //                          0b111000
    InstNop, //                          0b111001
    InstNop, //                          0b111010
    InstNop, //                          0b111011
    InstNop, //                          0b111100
    InstNop, //                          0b111101
    InstNop, //                          0b111110
    InstNop, //                          0b111111
};

MipsInstruction g_MipsInstructionsFPUW[] = {
    InstNop, //                       0b000000
    InstNop, //                       0b000001
    InstNop, //                       0b000010
    InstNop, //                       0b000011
    InstNop, //                       0b000100
    InstNop, //                       0b000101
    InstNop, //                       0b000110
    InstNop, //                       0b000111
    InstNop, //                       0b001000
    InstNop, //                       0b001001
    InstNop, //                       0b001010
    InstNop, //                       0b001011
    InstNop, //                       0b001100
    InstNop, //                       0b001101
    InstNop, //                       0b001110
    InstNop, //                       0b001111
    InstNop, //                       0b010000
    InstNop, //                       0b010001
    InstNop, //                       0b010010
    InstNop, //                       0b010011
    InstNop, //                       0b010100
    InstNop, //                       0b010101
    InstNop, //                       0b010110
    InstNop, //                       0b010111
    InstNop, //                       0b011000
    InstNop, //                       0b011001
    InstNop, //                       0b011010
    InstNop, //                       0b011011
    InstNop, //                       0b011100
    InstNop, //                       0b011101
    InstNop, //                       0b011110
    InstNop, //                       0b011111
    InstFPUWType("cvt.s.w", OL_FD_FS, 0b100000),
    InstNop, //                       0b100001
    InstNop, //                       0b100010
    InstNop, //                       0b100011
    InstNop, //                       0b100100
    InstNop, //                       0b100101
    InstNop, //                       0b100110
    InstNop, //                       0b100111
    InstNop, //                       0b101000
    InstNop, //                       0b101001
    InstNop, //                       0b101010
    InstNop, //                       0b101011
    InstNop, //                       0b101100
    InstNop, //                       0b101101
    InstNop, //                       0b101110
    InstNop, //                       0b101111
    InstNop, //                       0b110000
    InstNop, //                       0b110001
    InstNop, //                       0b110010
    InstNop, //                       0b110011
    InstNop, //                       0b110100
    InstNop, //                       0b110101
    InstNop, //                       0b110110
    InstNop, //                       0b110111
    InstNop, //                       0b111000
    InstNop, //                       0b111001
    InstNop, //                       0b111010
    InstNop, //                       0b111011
    InstNop, //                       0b111100
    InstNop, //                       0b111101
    InstNop, //                       0b111110
    InstNop, //                       0b111111
};

MipsInstruction g_MipsInstructionsCOP2[] = {
    InstNop, //                     0b00000
    InstCOP2Type("qmfc2", OL_RT_VD, 0b00001),
    InstCOP2Type("cfc2",  OL_RT_VD, 0b00010),
    InstNop, //                     0b00011
    InstNop, //                     0b00100
    InstCOP2Type("qmtc2", OL_RT_VD, 0b00101),
    InstCOP2Type("ctc2",  OL_RT_VD, 0b00110),
    InstNop, //                     0b00111
    InstNop, // BC2                 0b01000
    InstNop, //                     0b01001
    InstNop, //                     0b01010
    InstNop, //                     0b01011
    InstNop, //                     0b01100
    InstNop, //                     0b01101
    InstNop, //                     0b01110
    InstNop, //                     0b01111
    InstNop, //                     0b10000
    InstNop, //                     0b10001
    InstNop, //                     0b10010
    InstNop, //                     0b10011
    InstNop, //                     0b10100
    InstNop, //                     0b10101
    InstNop, //                     0b10110
    InstNop, //                     0b10111
    InstNop, //                     0b11000
    InstNop, //                     0b11001
    InstNop, //                     0b11010
    InstNop, //                     0b11011
    InstNop, //                     0b11100
    InstNop, //                     0b11101
    InstNop, //                     0b11110
    InstNop, //                     0b11111
};

MipsInstruction g_MipsInstructionsBC2[] = {
    InstBC2Type("bc2f",  OL_TARGET, 0b00000),
    InstBC2Type("bc2t",  OL_TARGET, 0b00001),
    InstBC2Type("bc2fl", OL_TARGET, 0b00010),
    InstBC2Type("bc2tl", OL_TARGET, 0b00011),
    InstNop, //                     0b00100
    InstNop, //                     0b00101
    InstNop, //                     0b00110
    InstNop, //                     0b00111
    InstNop, //                     0b01000
    InstNop, //                     0b01001
    InstNop, //                     0b01010
    InstNop, //                     0b01011
    InstNop, //                     0b01100
    InstNop, //                     0b01101
    InstNop, //                     0b01110
    InstNop, //                     0b01111
    InstNop, //                     0b10000
    InstNop, //                     0b10001
    InstNop, //                     0b10010
    InstNop, //                     0b10011
    InstNop, //                     0b10100
    InstNop, //                     0b10101
    InstNop, //                     0b10110
    InstNop, //                     0b10111
    InstNop, //                     0b11000
    InstNop, //                     0b11001
    InstNop, //                     0b11010
    InstNop, //                     0b11011
    InstNop, //                     0b11100
    InstNop, //                     0b11101
    InstNop, //                     0b11110
    InstNop, //                     0b11111
};

MipsInstruction g_MipsInstructionsCOP2S1[] = {
    InstCOP2Spec1Type("vaddx",   OL_VD_VS_VT,  0b000000),
    InstCOP2Spec1Type("vaddy",   OL_VD_VS_VT,  0b000001),
    InstCOP2Spec1Type("vaddz",   OL_VD_VS_VT,  0b000010),
    InstCOP2Spec1Type("vaddw",   OL_VD_VS_VT,  0b000011),
    InstCOP2Spec1Type("vsubx",   OL_VD_VS_VT,  0b000100),
    InstCOP2Spec1Type("vsuby",   OL_VD_VS_VT,  0b000101),
    InstCOP2Spec1Type("vsubz",   OL_VD_VS_VT,  0b000110),
    InstCOP2Spec1Type("vsubw",   OL_VD_VS_VT,  0b000111),
    InstCOP2Spec1Type("vmaddx",  OL_VD_VS_VT,  0b001000),
    InstCOP2Spec1Type("vmaddy",  OL_VD_VS_VT,  0b001001),
    InstCOP2Spec1Type("vmaddz",  OL_VD_VS_VT,  0b001010),
    InstCOP2Spec1Type("vmaddw",  OL_VD_VS_VT,  0b001011),
    InstCOP2Spec1Type("vmsubx",  OL_VD_VS_VT,  0b001100),
    InstCOP2Spec1Type("vmsuby",  OL_VD_VS_VT,  0b001101),
    InstCOP2Spec1Type("vmsubz",  OL_VD_VS_VT,  0b001110),
    InstCOP2Spec1Type("vmsubw",  OL_VD_VS_VT,  0b001111),
    InstCOP2Spec1Type("vmaxx",   OL_VD_VS_VT,  0b010000),
    InstCOP2Spec1Type("vmaxy",   OL_VD_VS_VT,  0b010001),
    InstCOP2Spec1Type("vmaxz",   OL_VD_VS_VT,  0b010010),
    InstCOP2Spec1Type("vmaxw",   OL_VD_VS_VT,  0b010011),
    InstCOP2Spec1Type("vminix",  OL_VD_VS_VT,  0b010100),
    InstCOP2Spec1Type("vminiy",  OL_VD_VS_VT,  0b010101),
    InstCOP2Spec1Type("vminiz",  OL_VD_VS_VT,  0b010110),
    InstCOP2Spec1Type("vminiw",  OL_VD_VS_VT,  0b010111),
    InstCOP2Spec1Type("vmulx",   OL_VD_VS_VT,  0b011000),
    InstCOP2Spec1Type("vmuly",   OL_VD_VS_VT,  0b011001),
    InstCOP2Spec1Type("vmulz",   OL_VD_VS_VT,  0b011010),
    InstCOP2Spec1Type("vmulw",   OL_VD_VS_VT,  0b011011),
    InstCOP2Spec1Type("vmulq",   OL_VD_VS_VT,  0b011100),
    InstCOP2Spec1Type("vmaxi",   OL_VD_VS_VT,  0b011101),
    InstCOP2Spec1Type("vmuli",   OL_VD_VS_VT,  0b011110),
    InstCOP2Spec1Type("vminii",  OL_VD_VS_VT,  0b011111),
    InstCOP2Spec1Type("vaddq",   OL_VD_VS_VT,  0b100000),
    InstCOP2Spec1Type("vmaddq",  OL_VD_VS_VT,  0b100001),
    InstCOP2Spec1Type("vaddi",   OL_VD_VS_VT,  0b100010),
    InstCOP2Spec1Type("vmaddi",  OL_VD_VS_VT,  0b100011),
    InstCOP2Spec1Type("vsubq",   OL_VD_VS_VT,  0b100100),
    InstCOP2Spec1Type("vmsubq",  OL_VD_VS_VT,  0b100101),
    InstCOP2Spec1Type("vsubi",   OL_VD_VS_VT,  0b100110),
    InstCOP2Spec1Type("vmsubi",  OL_VD_VS_VT,  0b100111),
    InstCOP2Spec1Type("vadd",    OL_VD_VS_VT,  0b101000),
    InstCOP2Spec1Type("vmadd",   OL_VD_VS_VT,  0b101001),
    InstCOP2Spec1Type("vmul",    OL_VD_VS_VT,  0b101010),
    InstCOP2Spec1Type("vmax",    OL_VD_VS_VT,  0b101011),
    InstCOP2Spec1Type("vsub",    OL_VD_VS_VT,  0b101100),
    InstCOP2Spec1Type("vmsub",   OL_VD_VS_VT,  0b101101),
    InstCOP2Spec1Type("vopmsub", OL_VD_VS_VT,  0b101110),
    InstCOP2Spec1Type("vmini",   OL_VD_VS_VT,  0b101111),
    InstCOP2Spec1Type("viadd",   OL_VD_VS_VT,  0b110000),
    InstCOP2Spec1Type("visub",   OL_VD_VS_VT,  0b110001),
    InstCOP2Spec1Type("viaddi",  OL_VT_VS_IMM, 0b110010),
    InstNop, //                                0b110011
    InstCOP2Spec1Type("viand",   OL_VD_VS_VT,  0b110100),
    InstCOP2Spec1Type("vior",    OL_VD_VS_VT,  0b110101),
    InstNop, //                                0b110110
    InstNop, //                                0b110111
    InstCOP2Spec1Type("vcallms", OL_TARGET,    0b111000),
    InstCOP2Spec1Type("vcallmsr",OL_VI27,      0b111001),
    InstNop, //                                0b111010
    InstNop, //                                0b111011
};

MipsInstruction g_MipsInstructionsCOP2S2[] = {
    InstCOP2Spec2Type("vaddax",   OL_ACC_VS_VT,   0b0000000),
    InstCOP2Spec2Type("vadday",   OL_ACC_VS_VT,   0b0000001),
    InstCOP2Spec2Type("vaddaz",   OL_ACC_VS_VT,   0b0000010),
    InstCOP2Spec2Type("vaddaw",   OL_ACC_VS_VT,   0b0000011),
    InstCOP2Spec2Type("vsubax",   OL_ACC_VS_VT,   0b0000100),
    InstCOP2Spec2Type("vsubay",   OL_ACC_VS_VT,   0b0000101),
    InstCOP2Spec2Type("vsubaz",   OL_ACC_VS_VT,   0b0000110),
    InstCOP2Spec2Type("vsubaw",   OL_ACC_VS_VT,   0b0000111),
    InstCOP2Spec2Type("vmaddax",  OL_ACC_VS_VT,   0b0001000),
    InstCOP2Spec2Type("vmadday",  OL_ACC_VS_VT,   0b0001001),
    InstCOP2Spec2Type("vmaddaz",  OL_ACC_VS_VT,   0b0001010),
    InstCOP2Spec2Type("vmaddaw",  OL_ACC_VS_VT,   0b0001011),
    InstCOP2Spec2Type("vmsubax",  OL_ACC_VS_VT,   0b0001100),
    InstCOP2Spec2Type("vmsubay",  OL_ACC_VS_VT,   0b0001101),
    InstCOP2Spec2Type("vmsubaz",  OL_ACC_VS_VT,   0b0001110),
    InstCOP2Spec2Type("vmsubaw",  OL_ACC_VS_VT,   0b0001111),
    InstCOP2Spec2Type("vitof0",   OL_VT_VS,   0b0010000),
    InstCOP2Spec2Type("vitof4",   OL_VT_VS,   0b0010001),
    InstCOP2Spec2Type("vitof12",  OL_VT_VS,   0b0010010),
    InstCOP2Spec2Type("vitof15",  OL_VT_VS,   0b0010011),
    InstCOP2Spec2Type("vftoi0",   OL_VT_VS,   0b0010100),
    InstCOP2Spec2Type("vftoi4",   OL_VT_VS,   0b0010101),
    InstCOP2Spec2Type("vftoi12",  OL_VT_VS,   0b0010110),
    InstCOP2Spec2Type("vftoi15",  OL_VT_VS,   0b0010111),
    InstCOP2Spec2Type("vmulax",   OL_ACC_VS_VT,   0b0011000),
    InstCOP2Spec2Type("vmulay",   OL_ACC_VS_VT,   0b0011001),
    InstCOP2Spec2Type("vmulaz",   OL_ACC_VS_VT,   0b0011010),
    InstCOP2Spec2Type("vmulaw",   OL_ACC_VS_VT,   0b0011011),
    InstCOP2Spec2Type("vmulaq",   OL_ACC_VS_VT,    0b0011100),
    InstCOP2Spec2Type("vabs",     OL_VT_VS,   0b0011101),
    InstCOP2Spec2Type("vmulai",   OL_ACC_VS_VT,    0b0011110),
    InstCOP2Spec2Type("vclipw",   OL_VT_VS,   0b0011111),
    InstCOP2Spec2Type("vaddaq",   OL_ACC_VS_VT,    0b0100000),
    InstCOP2Spec2Type("vmaddaq",  OL_ACC_VS_VT,    0b0100001),
    InstCOP2Spec2Type("vaddai",   OL_ACC_VS_VT,    0b0100010),
    InstCOP2Spec2Type("vmaddai",  OL_ACC_VS_VT,    0b0100011),
    InstCOP2Spec2Type("vsubaq",   OL_ACC_VS_VT,    0b0100100),
    InstCOP2Spec2Type("vmsubaq",  OL_ACC_VS_VT,    0b0100101),
    InstCOP2Spec2Type("vsubai",   OL_ACC_VS_VT,    0b0100110),
    InstCOP2Spec2Type("vmsubai",  OL_ACC_VS_VT,    0b0100111),
    InstCOP2Spec2Type("vadda",    OL_ACC_VS_VT,   0b0101000),
    InstCOP2Spec2Type("vmadda",   OL_ACC_VS_VT,   0b0101001),
    InstCOP2Spec2Type("vmula",    OL_ACC_VS_VT,   0b0101010),
    InstNop, //                            0b0101011
    InstCOP2Spec2Type("vsuba",    OL_ACC_VS_VT,   0b0101100),
    InstCOP2Spec2Type("vmsuba",   OL_ACC_VS_VT,   0b0101101),
    InstCOP2Spec2Type("vopmula",  OL_ACC_VS_VT,   0b0101110),
    InstCOP2Spec2Type("vnop",     OL_NONE, 0b0101111),
    InstCOP2Spec2Type("vmove",    OL_VT_VS,   0b0110000),
    InstCOP2Spec2Type("vmr32",    OL_VT_VS,   0b0110001),
    InstNop, //                            0b0110010
    InstNop, //                            0b0110011
    InstCOP2Spec2Type("vlqi",     OL_VT_VS,   0b0110100),
    InstCOP2Spec2Type("vsqi",     OL_VT_VS,   0b0110101),
    InstCOP2Spec2Type("vlqd",     OL_VT_VS,   0b0110110),
    InstCOP2Spec2Type("vsqd",     OL_VT_VS,   0b0110111),
    InstCOP2Spec2Type("vdiv",     OL_VT_VS,   0b0111000),
    InstCOP2Spec2Type("vsqrt",    OL_VT_VS,   0b0111001),
    InstCOP2Spec2Type("vrsqrt",   OL_VT_VS,   0b0111010),
    InstCOP2Spec2Type("vwaitq",   OL_NONE, 0b0111011),
    InstCOP2Spec2Type("vmtir",    OL_VT_VS,   0b0111100),
    InstCOP2Spec2Type("vmfir",    OL_VT_VS,   0b0111101),
    InstCOP2Spec2Type("vilwr",    OL_VT_VS,   0b0111110),
    InstCOP2Spec2Type("viswr",    OL_VT_VS,   0b0111111),
    InstCOP2Spec2Type("vrnext",   OL_VT_VS,   0b1000000),
    InstCOP2Spec2Type("vrget",    OL_VT_VS,   0b1000001),
    InstCOP2Spec2Type("vrinit",   OL_VT_VS,   0b1000010),
    InstCOP2Spec2Type("vrxor",    OL_VT_VS,   0b1000011),
    InstNop, //                            0b1000100
    InstNop, //                            0b1000101
    InstNop, //                            0b1000110
    InstNop, //                            0b1000111
    InstNop, //                            0b1001000
    InstNop, //                            0b1001001
    InstNop, //                            0b1001010
    InstNop, //                            0b1001011
    InstNop, //                            0b1001100
    InstNop, //                            0b1001101
    InstNop, //                            0b1001110
    InstNop, //                            0b1001111
    InstNop, //                            0b1010000
    InstNop, //                            0b1010001
    InstNop, //                            0b1010010
    InstNop, //                            0b1010011
    InstNop, //                            0b1010100
    InstNop, //                            0b1010101
    InstNop, //                            0b1010110
    InstNop, //                            0b1010111
    InstNop, //                            0b1011000
    InstNop, //                            0b1011001
    InstNop, //                            0b1011010
    InstNop, //                            0b1011011
    InstNop, //                            0b1011100
    InstNop, //                            0b1011101
    InstNop, //                            0b1011110
    InstNop, //                            0b1011111
    InstNop, //                            0b1100000
    InstNop, //                            0b1100001
    InstNop, //                            0b1100010
    InstNop, //                            0b1100011
    InstNop, //                            0b1100100
    InstNop, //                            0b1100101
    InstNop, //                            0b1100110
    InstNop, //                            0b1100111
    InstNop, //                            0b1101000
    InstNop, //                            0b1101001
    InstNop, //                            0b1101010
    InstNop, //                            0b1101011
    InstNop, //                            0b1101100
    InstNop, //                            0b1101101
    InstNop, //                            0b1101110
    InstNop, //                            0b1101111
    InstNop, //                            0b1110000
    InstNop, //                            0b1110001
    InstNop, //                            0b1110010
    InstNop, //                            0b1110011
    InstNop, //                            0b1110100
    InstNop, //                            0b1110101
    InstNop, //                            0b1110110
    InstNop, //                            0b1110111
    InstNop, //                            0b1111000
    InstNop, //                            0b1111001
    InstNop, //                            0b1111010
    InstNop, //                            0b1111011
    InstNop, //                            0b1111100
    InstNop, //                            0b1111101
    InstNop, //                            0b1111110
    InstNop, //                            0b1111111
};

MipsInstruction* FindInstruction(u32 instruction)
{
    MipsInstruction* nop = g_MipsInstructionsIJ;

    if(instruction == 0x00000000) return nop;

    u8 opcode = (instruction >> 26) & 0b111111;

    MipsInstruction* cur = g_MipsInstructionsIJ + opcode;

    if(cur->type != ITYPE_NOP)
        return cur;
    // R-Type
    if(opcode == 0b000000) {
        u8 funct = instruction & 0b111111;
        cur = g_MipsInstructionsR + funct;
        if(cur->type != ITYPE_NOP)
            return cur;
        return nullptr;
    }
    // REGIMM
    else if(opcode == 0b000001) {
        u8 rt = (instruction >> 16) & 0b11111;
        cur = g_MipsInstructionsREGIMM + rt;
        if(cur->type != ITYPE_NOP)
            return cur;
        return nullptr;
    }
    // COP0
    else if(opcode == 0b010000) {
        u8 fmt = (instruction >> 21) & 0b11111;
        // BC0
        if(fmt == 0b01000) {
            fmt = (instruction >> 16) & 0b11111;
            cur = g_MipsInstructionsBC0 + fmt;
        }
        // TLB
        else if(fmt == 0b10000) {
            fmt = instruction & 0b111111;
            cur = g_MipsInstructionsTLB + fmt;
        }
        else
            cur = g_MipsInstructionsCOP0 + fmt;

        if(cur->type != ITYPE_NOP)
            return cur;
        return nullptr;
    }
    // COP1
    else if(opcode == 0b010001) {
        u8 fmt = (instruction >> 21) & 0b11111;
        // BC1
        if(fmt == 0b01000) {
            fmt = (instruction >> 16) & 0b11111;
            cur = g_MipsInstructionsBC1 + fmt;
        }
        // FPU.S
        else if(fmt == 0b10000) {
            fmt = instruction & 0b111111;
            cur = g_MipsInstructionsFPUS + fmt;
        }
        // FPU.W
        else if(fmt == 0b10100) {
            fmt = instruction & 0b111111;
            cur = g_MipsInstructionsFPUW + fmt;
        }
        else
            cur = g_MipsInstructionsCOP1 + fmt;

        if(cur->type != ITYPE_NOP)
            return cur;
        return nullptr;
    }
    // COP2
    else if(opcode == 0b010010) {
        u8 fmt = (instruction >> 21) & 0b11111;
        // BC2
        if(fmt == 0b01000) {
            fmt = (instruction >> 16) & 0b11111;
            cur = g_MipsInstructionsBC2 + fmt;
        }
        // Special 1
        else if(fmt & 0b10000) {
            fmt = instruction & 0b111111;
            // Special 2
            if((fmt & 0b111100) == 0b111100) {
                fmt = (instruction & 0b11) | (((instruction >> 6) & 0b11111) * 4);
                cur = g_MipsInstructionsCOP2S2 + fmt;
            }
            else
                cur = g_MipsInstructionsCOP2S1 + fmt;
        }
        else
            cur = g_MipsInstructionsCOP2 + fmt;

        if(cur->type != ITYPE_NOP)
            return cur;
        return nullptr;
    }
    // MMI
    else if(opcode == 0b011100) {
        u8 funct = instruction & 0b111111;
        MipsInstruction* arr = g_MipsInstructionsMMI;
        // MMI0
        if(funct == 0b001000) {
            funct = (instruction >> 6) & 0b11111;
            arr = g_MipsInstructionsMMI0;
        }
        else if(funct == 0b001001) {
            funct = (instruction >> 6) & 0b11111;
            arr = g_MipsInstructionsMMI2;
        }
        else if(funct == 0b101000) {
            funct = (instruction >> 6) & 0b11111;
            arr = g_MipsInstructionsMMI1;
        }
        else if(funct == 0b101001) {
            funct = (instruction >> 6) & 0b11111;
            arr = g_MipsInstructionsMMI3;
        }
        cur = arr + funct;
        if(cur->type != ITYPE_NOP)
            return cur;
        return nullptr;
    }

    return nullptr;
}
