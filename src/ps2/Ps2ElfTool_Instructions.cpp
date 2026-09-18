#include "Ps2ElfTool_Instructions.h"

MipsInstruction g_MipsInstructionsIJ[] = {
    InstNop, // R-Type                0b000000
    InstNop, // REGIMM                0b000001
    InstJType("j",     OL_TARGET,     0b000010),
    InstJType("jal",   OL_TARGET,     0b000011),
    InstIType("beq",   OL_RR_TARGET,  0b000100),
    InstIType("bne",   OL_RR_TARGET,  0b000101),
    InstIType("blez",  OL_R_TARGET,   0b000110),
    InstIType("bgtz",  OL_R_TARGET,   0b000111),
    InstIType("addi",  OL_RRI,        0b001000),
    InstIType("addiu", OL_RRI,        0b001001),
    InstIType("slti",  OL_RRI,        0b001010),
    InstIType("sltiu", OL_RRI,        0b001011),
    InstIType("andi",  OL_RRI,        0b001100),
    InstIType("ori",   OL_RRI,        0b001101),
    InstIType("xori",  OL_RRI,        0b001110),
    InstIType("lui",   OL_RI,         0b001111),
    InstNop, // COP0                  0b010000
    InstNop, // COP1                  0b010001
    InstNop, // COP2                  0b010010
    InstNop, //                       0b010011
    InstIType("beql",  OL_RR_TARGET,  0b010100),
    InstIType("bnel",  OL_RR_TARGET,  0b010101),
    InstIType("blezl", OL_R_TARGET,   0b010110),
    InstIType("bgtzl", OL_R_TARGET,   0b010111),
    InstIType("daddi", OL_RRI,        0b011000),
    InstIType("daddiu",OL_RRI,        0b011001),
    InstIType("ldl",   OL_RR_OFFSET,  0b011010),
    InstIType("ldr",   OL_RR_OFFSET,  0b011011),
    InstNop, // MMI                   0b011100
    InstNop, //                       0b011101
    InstIType("lq",    OL_RR_OFFSET,  0b011110),
    InstIType("sq",    OL_RR_OFFSET,  0b011111),
    InstIType("lb",    OL_RR_OFFSET,  0b100000),
    InstIType("lh",    OL_RR_OFFSET,  0b100001),
    InstIType("lwl",   OL_RR_OFFSET,  0b100010),
    InstIType("lw",    OL_RR_OFFSET,  0b100011),
    InstIType("lbu",   OL_RR_OFFSET,  0b100100),
    InstIType("lhu",   OL_RR_OFFSET,  0b100101),
    InstIType("lwr",   OL_RR_OFFSET,  0b100110),
    InstIType("lwu",   OL_RR_OFFSET,  0b100111),
    InstIType("sb",    OL_RR_OFFSET,  0b101000),
    InstIType("sh",    OL_RR_OFFSET,  0b101001),
    InstIType("swl",   OL_RR_OFFSET,  0b101010),
    InstIType("sw",    OL_RR_OFFSET,  0b101011),
    InstIType("sdl",   OL_RR_OFFSET,  0b101100),
    InstIType("sdr",   OL_RR_OFFSET,  0b101101),
    InstIType("swr",   OL_RR_OFFSET,  0b101110),
    InstIType("cache", OL_RR_OFFSET,  0b101111),
    InstNop, //                       0b110000
    InstIType("lwc1",  OL_FRR_OFFSET, 0b110001),
    InstNop, //                       0b110010
    InstIType("pref",  OL_HINT,       0b110011),
    InstNop, //                       0b110100
    InstNop, //                       0b110101
    InstIType("lqc2",  OL_VRR_OFFSET, 0b110110),
    InstIType("ld",    OL_RR_OFFSET,  0b110111),
    InstNop, //                       0b111000
    InstIType("swc1",  OL_FRR_OFFSET, 0b111001),
    InstNop, //                       0b111010
    InstNop, //                       0b111011
    InstNop, //                       0b111100
    InstNop, //                       0b111101
    InstIType("sqc2",  OL_VRR_OFFSET, 0b111110),
    InstIType("sd",    OL_RR_OFFSET,  0b111111),
};

MipsInstruction g_MipsInstructionsR[] = {
    InstRType("sll",     OL_RR_SHIFT, 0b000000),
    InstNop, //                       0b000001
    InstRType("srl",     OL_RR_SHIFT, 0b000010),
    InstRType("sra",     OL_RR_SHIFT, 0b000011),
    InstRType("sllv",    OL_RRR,      0b000100),
    InstNop, //                       0b110101
    InstRType("srlv",    OL_RRR,      0b000110),
    InstRType("srav",    OL_RRR,      0b000111),
    InstRType("jr",      OL_R,        0b001000),
    InstRType("jalr",    OL_RR,       0b001001),
    InstRType("movz",    OL_RRR,      0b001010),
    InstRType("movn",    OL_RRR,      0b001011),
    InstRType("syscall", OL_NONE,     0b001100),
    InstRType("break",   OL_NONE,     0b001101),
    InstNop, //                       0b001110
    InstRType("sync",    OL_NONE,     0b001111),
    InstRType("mfhi",    OL_R,        0b010000),
    InstRType("mthi",    OL_R,        0b010001),
    InstRType("mflo",    OL_R,        0b010010),
    InstRType("mtlo",    OL_R,        0b010011),
    InstRType("dsllv",   OL_RRR,      0b010100),
    InstNop, //                       0b010101
    InstRType("dsrlv",   OL_RRR,      0b010110),
    InstRType("dsrav",   OL_RRR,      0b010111),
    InstRType("mult",    OL_RR,       0b011000),
    InstRType("multu",   OL_RR,       0b011001),
    InstRType("div",     OL_RR,       0b011010),
    InstRType("divu",    OL_RR,       0b011011),
    InstNop, //                       0b011100
    InstNop, //                       0b011101
    InstNop, //                       0b011110
    InstNop, //                       0b011111
    InstRType("add",     OL_RRR,      0b100000),
    InstRType("addu",    OL_RRR,      0b100001),
    InstRType("sub",     OL_RRR,      0b100010),
    InstRType("subu",     OL_RRR,     0b100011),
    InstRType("and",     OL_RRR,      0b100100),
    InstRType("or",      OL_RRR,      0b100101),
    InstRType("xor",     OL_RRR,      0b100110),
    InstRType("nor",     OL_RRR,      0b100111),
    InstRType("mfsa",    OL_R,        0b101000),
    InstRType("mtsa",    OL_R,        0b101001),
    InstRType("slt",     OL_RRR,      0b101010),
    InstRType("sltu",    OL_RRR,      0b101011),
    InstRType("dadd",    OL_RRR,      0b101100),
    InstRType("daddu",   OL_RRR,      0b101101),
    InstRType("dsub",    OL_RRR,      0b101110),
    InstRType("dsubu",   OL_RRR,      0b101111),
    InstRType("tge",     OL_RR,       0b110000),
    InstRType("tgeu",    OL_RR,       0b110001),
    InstRType("tlt",     OL_RR,       0b110010),
    InstRType("tltu",    OL_RR,       0b110011),
    InstRType("teq",     OL_RR,       0b110100),
    InstNop, //                       0b110101
    InstRType("tne",     OL_RR,       0b110110),
    InstNop, //                       0b110111
    InstRType("dsll",    OL_RR_SHIFT, 0b111000),
    InstNop, //                       0b111001
    InstRType("dsrl",    OL_RR_SHIFT, 0b111010),
    InstRType("dsra",    OL_RR_SHIFT, 0b111011),
    InstRType("dsll32",  OL_RR_SHIFT, 0b111100),
    InstNop, //                       0b111101
    InstRType("dsrl32",  OL_RR_SHIFT, 0b111110),
    InstRType("dsra32",  OL_RR_SHIFT, 0b111111),
};

MipsInstruction g_MipsInstructionsMMI[] = {
    InstMMIType("madd",   OL_RRR,      0b000000),
    InstMMIType("maddu",  OL_RRR,      0b000001),
    InstNop, //                        0b000010
    InstNop, //                        0b000011
    InstMMIType("plzcw",  OL_RR,       0b000100),
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
    InstMMIType("mfhi1",  OL_R,        0b010000),
    InstMMIType("mthi1",  OL_R,        0b010001),
    InstMMIType("mflo1",  OL_R,        0b010010),
    InstMMIType("mtlo1",  OL_R,        0b010011),
    InstNop, //                        0b010100,
    InstNop, //                        0b010101,
    InstNop, //                        0b010110
    InstNop, //                        0b010111
    InstMMIType("mult1",  OL_RRR,      0b011000),
    InstMMIType("multu1", OL_RRR,      0b011001),
    InstMMIType("div1",   OL_RRR,      0b011010),
    InstMMIType("divu1",  OL_RRR,      0b011011),
    InstNop, //                        0b011100
    InstNop, //                        0b011101
    InstNop, //                        0b011110
    InstNop, //                        0b011111
    InstMMIType("madd1",  OL_RRR,      0b100000),
    InstMMIType("maddu1", OL_RRR,      0b100001),
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
    InstMMIType("pmfhl",  OL_R,        0b110000),
    InstMMIType("pmthl",  OL_R,        0b110001),
    InstNop, //                        0b110010
    InstNop, //                        0b110011
    InstMMIType("psllh",  OL_RR_SHIFT, 0b110100),
    InstNop, //                        0b110101
    InstMMIType("psrlh",  OL_RR_SHIFT, 0b110110),
    InstMMIType("psrah",  OL_RR_SHIFT, 0b110111),
    InstNop, //                        0b111000
    InstNop, //                        0b111001
    InstNop, //                        0b111010
    InstNop, //                        0b111011
    InstMMIType("psllw",  OL_RR_SHIFT, 0b111100),
    InstNop, //                        0b111101
    InstMMIType("psrlw",  OL_RR_SHIFT, 0b111110),
    InstMMIType("psraw",  OL_RR_SHIFT, 0b111111)
};

MipsInstruction g_MipsInstructionsMMI0[] = {
    InstMMI0Type("paddw",  OL_RRR, 0b00000),
    InstMMI0Type("psubw",  OL_RRR, 0b00001),
    InstMMI0Type("pcgtw",  OL_RRR, 0b00010),
    InstMMI0Type("pmaxw",  OL_RRR, 0b00011),
    InstMMI0Type("paddh",  OL_RRR, 0b00100),
    InstMMI0Type("psubh",  OL_RRR, 0b00101),
    InstMMI0Type("pcgth",  OL_RRR, 0b00110),
    InstMMI0Type("pmaxh",  OL_RRR, 0b00111),
    InstMMI0Type("paddb",  OL_RRR, 0b01000),
    InstMMI0Type("psubb",  OL_RRR, 0b01001),
    InstMMI0Type("pcgtb",  OL_RRR, 0b01010),
    InstNop, //                    0b01011
    InstNop, //                    0b01100
    InstNop, //                    0b01101
    InstNop, //                    0b01110
    InstNop, //                    0b01111
    InstMMI0Type("paddsw", OL_RRR, 0b10000),
    InstMMI0Type("psubsw", OL_RRR, 0b10001),
    InstMMI0Type("pextlw", OL_RRR, 0b10010),
    InstMMI0Type("ppacw",  OL_RRR, 0b10011),
    InstMMI0Type("paddsh", OL_RRR, 0b10100),
    InstMMI0Type("psubsh", OL_RRR, 0b10101),
    InstMMI0Type("pextlh", OL_RRR, 0b10110),
    InstMMI0Type("ppach",  OL_RRR, 0b10111),
    InstMMI0Type("paddsb", OL_RRR, 0b11000),
    InstMMI0Type("psubsb", OL_RRR, 0b11001),
    InstMMI0Type("pextlb", OL_RRR, 0b11010),
    InstMMI0Type("ppacb",  OL_RRR, 0b11011),
    InstNop, //                    0b11100
    InstNop, //                    0b11101
    InstMMI0Type("pext5",  OL_RR,  0b11110),
    InstMMI0Type("ppac5",  OL_RR,  0b11111)
};

MipsInstruction g_MipsInstructionsMMI1[] = {
    InstNop, //                    0b00000
    InstMMI1Type("pabsw",  OL_RR,  0b00001),
    InstMMI1Type("pceqw",  OL_RRR, 0b00010),
    InstMMI1Type("pminw",  OL_RRR, 0b00011),
    InstMMI1Type("padsbh", OL_RRR, 0b00100),
    InstMMI1Type("pabsh",  OL_RR,  0b00101),
    InstMMI1Type("pceqh",  OL_RRR, 0b00110),
    InstMMI1Type("pminh",  OL_RRR, 0b00111),
    InstNop, //                    0b01000
    InstNop, //                    0b01001
    InstMMI1Type("pceqb",  OL_RRR, 0b01010),
    InstNop, //                    0b01011
    InstNop, //                    0b01100
    InstNop, //                    0b01101
    InstNop, //                    0b01110
    InstNop, //                    0b01111
    InstMMI1Type("padduw", OL_RRR, 0b10000),
    InstMMI1Type("psubuw", OL_RRR, 0b10001),
    InstMMI1Type("pextuw", OL_RRR, 0b10010),
    InstNop, //                    0b10111
    InstMMI1Type("padduh", OL_RRR, 0b10100),
    InstMMI1Type("psubuh", OL_RRR, 0b10101),
    InstMMI1Type("pextuh", OL_RRR, 0b10110),
    InstNop, //                    0b10111
    InstMMI1Type("paddub", OL_RRR, 0b11000),
    InstMMI1Type("psubub", OL_RRR, 0b11001),
    InstMMI1Type("pextub", OL_RRR, 0b11010),
    InstMMI1Type("qfsrv",  OL_RRR, 0b11011),
    InstNop, //                    0b11100
    InstNop, //                    0b11101
    InstNop, //                    0b11110
    InstNop, //                    0b11111
};

MipsInstruction g_MipsInstructionsMMI2[] = {
    InstMMI2Type("pmaddw",  OL_RRR, 0b00000),
    InstNop, //                     0b00001
    InstMMI2Type("psllvw",  OL_RRR, 0b00010),
    InstMMI2Type("psrlvw",  OL_RRR, 0b00011),
    InstMMI2Type("pmsubw",  OL_RRR, 0b00100),
    InstNop, //                     0b00101
    InstNop, //                     0b00110
    InstNop, //                     0b00111
    InstMMI2Type("pmfhi",   OL_R,   0b01000),
    InstMMI2Type("pmflo",   OL_R,   0b01001),
    InstMMI2Type("pinth",   OL_RRR, 0b01010),
    InstNop, //                     0b01011
    InstMMI2Type("pmultw",  OL_RRR, 0b01100),
    InstMMI2Type("pdivw",   OL_RR,  0b01101),
    InstMMI2Type("pcpyld",  OL_RRR, 0b01110),
    InstNop, //                     0b01111
    InstMMI2Type("pmaddh",  OL_RRR, 0b10000),
    InstMMI2Type("phmadh",  OL_RRR, 0b10001),
    InstMMI2Type("pand",    OL_RRR, 0b10010),
    InstMMI2Type("pxor",    OL_RRR, 0b10011),
    InstMMI2Type("pmsubh",  OL_RRR, 0b10100),
    InstMMI2Type("phmsbh",  OL_RRR, 0b10101),
    InstNop, //                     0b10110
    InstNop, //                     0b10111
    InstNop, //                     0b11000
    InstNop, //                     0b11001
    InstMMI2Type("pexeh",   OL_RR,  0b11010),
    InstMMI2Type("prevh",   OL_RR,  0b11011),
    InstMMI2Type("pmulth",  OL_RRR, 0b11100),
    InstMMI2Type("pdivbw",  OL_RR,  0b11101),
    InstMMI2Type("pexew",   OL_RR,  0b11110),
    InstMMI2Type("prot3w",  OL_RR,  0b11111)
};

MipsInstruction g_MipsInstructionsMMI3[] = {
    InstMMI3Type("pmadduw", OL_RRR, 0b00000),
    InstNop, //                     0b00001
    InstNop, //                     0b00010
    InstMMI3Type("psravw",  OL_RRR, 0b00011),
    InstNop, //                     0b00100
    InstNop, //                     0b00101
    InstNop, //                     0b00110
    InstNop, //                     0b00111
    InstMMI3Type("pmthi",   OL_R,   0b01000),
    InstMMI3Type("pmtlo",   OL_R,   0b01001),
    InstMMI3Type("pinteh",  OL_RRR, 0b01010),
    InstNop, //                     0b01011
    InstMMI3Type("pmultuw", OL_RRR, 0b01100),
    InstMMI3Type("pdivuw",  OL_RR,  0b01101),
    InstMMI3Type("pcpyud",  OL_RRR, 0b01110),
    InstNop, //                     0b01111
    InstNop, //                     0b10000
    InstNop, //                     0b10001
    InstMMI3Type("por",     OL_RRR, 0b10010),
    InstMMI3Type("pnor",    OL_RRR, 0b10011),
    InstNop, //                     0b10100
    InstNop, //                     0b10101
    InstNop, //                     0b10110
    InstNop, //                     0b10111
    InstNop, //                     0b11000
    InstNop, //                     0b11001
    InstMMI3Type("pexch",   OL_RR,  0b11010),
    InstMMI3Type("pcpyh",   OL_RR,  0b11011),
    InstNop, //                     0b11100
    InstNop, //                     0b11101
    InstMMI3Type("pexcw",   OL_RR,  0b11110),
    InstNop, //                     0b11111
};

MipsInstruction g_MipsInstructionsREGIMM[] = {
    InstREGIMMType("bltz",    OL_R_TARGET, 0b00000),
    InstREGIMMType("bgez",    OL_R_TARGET, 0b00001),
    InstREGIMMType("bltzl",   OL_R_TARGET, 0b00010),
    InstREGIMMType("bgezl",   OL_R_TARGET, 0b00011),
    InstNop, //                            0b00100
    InstNop, //                            0b00101
    InstNop, //                            0b00110
    InstNop, //                            0b00111
    InstREGIMMType("tgei",    OL_RSI,      0b01000),
    InstREGIMMType("tgeiu",   OL_RSI,      0b01001),
    InstREGIMMType("tlti",    OL_RSI,      0b01010),
    InstREGIMMType("tltiu",   OL_RSI,      0b01011),
    InstREGIMMType("teqi",    OL_RSI,      0b01100),
    InstNop, //                            0b01101
    InstREGIMMType("tnei",    OL_RSI,      0b01110),
    InstNop, //                            0b01111
    InstREGIMMType("bltzal",  OL_R_TARGET, 0b10000),
    InstREGIMMType("bgezal",  OL_R_TARGET, 0b10001),
    InstREGIMMType("bltzall", OL_R_TARGET, 0b10010),
    InstREGIMMType("bgezall", OL_R_TARGET, 0b10011),
    InstNop, //                            0b10100
    InstNop, //                            0b10101
    InstNop, //                            0b10110
    InstNop, //                            0b10111
    InstREGIMMType("mtsab",   OL_RSI,      0b11000),
    InstREGIMMType("mtsah",   OL_RSI,      0b11001),
    InstNop, //                            0b11010
    InstNop, //                            0b11011
    InstNop, //                            0b11100
    InstNop, //                            0b11101
    InstNop, //                            0b11110
    InstNop, //                            0b11111
};

MipsInstruction g_MipsInstructionsCOP0[] = {
    InstCOP0Type("mfc0", OL_RC0,  0b00000),
    InstNop, //                   0b00001
    InstNop, //                   0b00010
    InstNop, //                   0b00011
    InstCOP0Type("mtc0", OL_RC0,  0b00100),
    InstNop, //                   0b00101
    InstNop, //                   0b00110
    InstNop, //                   0b00111
    InstNop, // BC0               0b01000
    InstNop, //                   0b01001
    InstNop, //                   0b01010
    InstNop, //                   0b01011
    InstNop, //                   0b01100
    InstNop, //                   0b01101
    InstNop, //                   0b01110
    InstNop, //                   0b01111
    InstNop, // TLB               0b10000
    InstNop, //                   0b10001
    InstNop, //                   0b10010
    InstNop, //                   0b10011
    InstNop, //                   0b10100
    InstNop, //                   0b10101
    InstNop, //                   0b10110
    InstNop, //                   0b10111
    InstNop, //                   0b11000
    InstNop, //                   0b11001
    InstNop, //                   0b11010
    InstNop, //                   0b11011
    InstNop, //                   0b11100
    InstNop, //                   0b11101
    InstNop, //                   0b11110
    InstNop, //                   0b11111
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
    InstCOP1Type("mfc1", OL_RFR, 0b00000),
    InstNop, //                 0b00001
    InstCOP1Type("cfc1", OL_RC1, 0b00010),
    InstNop, //                 0b00011
    InstCOP1Type("mtc1", OL_RFR, 0b00100),
    InstNop, //                 0b00101
    InstCOP1Type("ctc1", OL_RC1, 0b00110),
    InstNop, //                 0b00111
    InstNop, // BC1             0b01000
    InstNop, //                 0b01001
    InstNop, //                 0b01010
    InstNop, //                 0b01011
    InstNop, //                 0b01100
    InstNop, //                 0b01101
    InstNop, //                 0b01110
    InstNop, //                 0b01111
    InstNop, // FPU.S           0b10000
    InstNop, //                 0b10001
    InstNop, //                 0b10010
    InstNop, //                 0b10011
    InstNop, // FPU.W           0b10100
    InstNop, //                 0b10101
    InstNop, //                 0b10110
    InstNop, //                 0b10111
    InstNop, //                 0b11000
    InstNop, //                 0b11001
    InstNop, //                 0b11010
    InstNop, //                 0b11011
    InstNop, //                 0b11100
    InstNop, //                 0b11101
    InstNop, //                 0b11110
    InstNop, //                 0b11111
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
    InstFPUSType("add.s",   OL_FRFRFR,      0b000000),
    InstFPUSType("sub.s",   OL_FRFRFR,      0b000001),
    InstFPUSType("mul.s",   OL_FRFRFR,      0b000010),
    InstFPUSType("div.s",   OL_FRFRFR,      0b000011),
    InstFPUSType("sqrt.s",  OL_FRFR,       0b000100),
    InstFPUSType("abs.s",   OL_FRFR,       0b000101),
    InstFPUSType("mov.s",   OL_FRFR,       0b000110),
    InstFPUSType("neg.s",   OL_FRFR,       0b000111),
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
    InstFPUSType("rsqrt.s", OL_FRFRFR,       0b010110),
    InstNop, //                          0b010111
    InstFPUSType("adda.s",  OL_FRFR,       0b011000),
    InstFPUSType("suba.s",  OL_FRFR,       0b011001),
    InstFPUSType("mula.s",  OL_FRFR,       0b011010),
    InstNop, //                          0b011011
    InstFPUSType("madd.s",  OL_FRFRFR,      0b011100),
    InstFPUSType("msub.s",  OL_FRFRFR,      0b011101),
    InstFPUSType("madda.s", OL_FRFR,       0b011110),
    InstFPUSType("msuba.s", OL_FRFR,       0b011111),
    InstNop, //                          0b100000
    InstNop, //                          0b100001
    InstNop, //                          0b100010
    InstNop, //                          0b100011
    InstFPUSType("cvt.w.s",   OL_FRFR,       0b100100),
    InstNop, //                          0b100101
    InstNop, //                          0b100110
    InstNop, //                          0b100111
    InstFPUSType("max.s",   OL_FRFRFR,      0b101000),
    InstFPUSType("min.s",   OL_FRFRFR,      0b101001),
    InstNop, //                          0b101010
    InstNop, //                          0b101011
    InstNop, //                          0b101100
    InstNop, //                          0b101101
    InstNop, //                          0b101110
    InstNop, //                          0b101111
    InstFPUSType("c.f.s",     OL_FRFR,       0b110000),
    InstNop, //                          0b110001
    InstFPUSType("c.eq.s",    OL_FRFR,       0b110010),
    InstNop, //                          0b110011
    InstFPUSType("c.lt.s",    OL_FRFR,       0b110100),
    InstNop, //                          0b100101
    InstFPUSType("c.le.s",    OL_FRFR,       0b110110),
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
    InstNop, //                      0b000000
    InstNop, //                      0b000001
    InstNop, //                      0b000010
    InstNop, //                      0b000011
    InstNop, //                      0b000100
    InstNop, //                      0b000101
    InstNop, //                      0b000110
    InstNop, //                      0b000111
    InstNop, //                      0b001000
    InstNop, //                      0b001001
    InstNop, //                      0b001010
    InstNop, //                      0b001011
    InstNop, //                      0b001100
    InstNop, //                      0b001101
    InstNop, //                      0b001110
    InstNop, //                      0b001111
    InstNop, //                      0b010000
    InstNop, //                      0b010001
    InstNop, //                      0b010010
    InstNop, //                      0b010011
    InstNop, //                      0b010100
    InstNop, //                      0b010101
    InstNop, //                      0b010110
    InstNop, //                      0b010111
    InstNop, //                      0b011000
    InstNop, //                      0b011001
    InstNop, //                      0b011010
    InstNop, //                      0b011011
    InstNop, //                      0b011100
    InstNop, //                      0b011101
    InstNop, //                      0b011110
    InstNop, //                      0b011111
    InstFPUWType("cvt.s.w", OL_FRFR, 0b100000),
    InstNop, //                      0b100001
    InstNop, //                      0b100010
    InstNop, //                      0b100011
    InstNop, //                      0b100100
    InstNop, //                      0b100101
    InstNop, //                      0b100110
    InstNop, //                      0b100111
    InstNop, //                      0b101000
    InstNop, //                      0b101001
    InstNop, //                      0b101010
    InstNop, //                      0b101011
    InstNop, //                      0b101100
    InstNop, //                      0b101101
    InstNop, //                      0b101110
    InstNop, //                      0b101111
    InstNop, //                      0b110000
    InstNop, //                      0b110001
    InstNop, //                      0b110010
    InstNop, //                      0b110011
    InstNop, //                      0b110100
    InstNop, //                      0b110101
    InstNop, //                      0b110110
    InstNop, //                      0b110111
    InstNop, //                      0b111000
    InstNop, //                      0b111001
    InstNop, //                      0b111010
    InstNop, //                      0b111011
    InstNop, //                      0b111100
    InstNop, //                      0b111101
    InstNop, //                      0b111110
    InstNop, //                      0b111111
};

MipsInstruction g_MipsInstructionsCOP2[] = {
    InstNop, //                   0b00000
    InstCOP2Type("qmfc2", OL_RR,  0b00001),
    InstCOP2Type("cfc2",  OL_RC2, 0b00010),
    InstNop, //                   0b00011
    InstNop, //                   0b00100
    InstCOP2Type("qmtc2", OL_RR,  0b00101),
    InstCOP2Type("ctc2",  OL_RC2, 0b00110),
    InstNop, //                   0b00111
    InstNop, // BC2               0b01000
    InstNop, //                   0b01001
    InstNop, //                   0b01010
    InstNop, //                   0b01011
    InstNop, //                   0b01100
    InstNop, //                   0b01101
    InstNop, //                   0b01110
    InstNop, //                   0b01111
    InstNop, //                   0b10000
    InstNop, //                   0b10001
    InstNop, //                   0b10010
    InstNop, //                   0b10011
    InstNop, //                   0b10100
    InstNop, //                   0b10101
    InstNop, //                   0b10110
    InstNop, //                   0b10111
    InstNop, //                   0b11000
    InstNop, //                   0b11001
    InstNop, //                   0b11010
    InstNop, //                   0b11011
    InstNop, //                   0b11100
    InstNop, //                   0b11101
    InstNop, //                   0b11110
    InstNop, //                   0b11111
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
    InstCOP2Spec1Type("vaddx",   OL_VRVRVR, 0b000000),
    InstCOP2Spec1Type("vaddy",   OL_VRVRVR,    0b000001),
    InstCOP2Spec1Type("vaddz",   OL_VRVRVR,    0b000010),
    InstCOP2Spec1Type("vaddw",   OL_VRVRVR,    0b000011),
    InstCOP2Spec1Type("vsubx",   OL_VRVRVR,    0b000100),
    InstCOP2Spec1Type("vsuby",   OL_VRVRVR,    0b000101),
    InstCOP2Spec1Type("vsubz",   OL_VRVRVR,    0b000110),
    InstCOP2Spec1Type("vsubw",   OL_VRVRVR,    0b000111),
    InstCOP2Spec1Type("vmaddx",  OL_VRVRVR,    0b001000),
    InstCOP2Spec1Type("vmaddy",  OL_VRVRVR,    0b001001),
    InstCOP2Spec1Type("vmaddz",  OL_VRVRVR,    0b001010),
    InstCOP2Spec1Type("vmaddw",  OL_VRVRVR,    0b001011),
    InstCOP2Spec1Type("vmsubx",  OL_VRVRVR,    0b001100),
    InstCOP2Spec1Type("vmsuby",  OL_VRVRVR,    0b001101),
    InstCOP2Spec1Type("vmsubz",  OL_VRVRVR,    0b001110),
    InstCOP2Spec1Type("vmsubw",  OL_VRVRVR,    0b001111),
    InstCOP2Spec1Type("vmaxx",   OL_VRVRVR,    0b010000),
    InstCOP2Spec1Type("vmaxy",   OL_VRVRVR,    0b010001),
    InstCOP2Spec1Type("vmaxz",   OL_VRVRVR,    0b010010),
    InstCOP2Spec1Type("vmaxw",   OL_VRVRVR,    0b010011),
    InstCOP2Spec1Type("vminix",  OL_VRVRVR,    0b010100),
    InstCOP2Spec1Type("vminiy",  OL_VRVRVR,    0b010101),
    InstCOP2Spec1Type("vminiz",  OL_VRVRVR,    0b010110),
    InstCOP2Spec1Type("vminiw",  OL_VRVRVR,    0b010111),
    InstCOP2Spec1Type("vmulx",   OL_VRVRVR,    0b011000),
    InstCOP2Spec1Type("vmuly",   OL_VRVRVR,    0b011001),
    InstCOP2Spec1Type("vmulz",   OL_VRVRVR,    0b011010),
    InstCOP2Spec1Type("vmulw",   OL_VRVRVR,    0b011011),
    InstCOP2Spec1Type("vmulq",   OL_VRVRVR,     0b011100),
    InstCOP2Spec1Type("vmaxi",   OL_VRVRVR,     0b011101),
    InstCOP2Spec1Type("vmuli",   OL_VRVRVR,     0b011110),
    InstCOP2Spec1Type("vminii",  OL_VRVRVR,     0b011111),
    InstCOP2Spec1Type("vaddq",   OL_VRVRVR,     0b100000),
    InstCOP2Spec1Type("vmaddq",  OL_VRVRVR,     0b100001),
    InstCOP2Spec1Type("vaddi",   OL_VRVRVR,     0b100010),
    InstCOP2Spec1Type("vmaddi",  OL_VRVRVR,     0b100011),
    InstCOP2Spec1Type("vsubq",   OL_VRVRVR,     0b100100),
    InstCOP2Spec1Type("vmsubq",  OL_VRVRVR,     0b100101),
    InstCOP2Spec1Type("vsubi",   OL_VRVRVR,     0b100110),
    InstCOP2Spec1Type("vmsubi",  OL_VRVRVR,     0b100111),
    InstCOP2Spec1Type("vadd",    OL_VRVRVR,    0b101000),
    InstCOP2Spec1Type("vmadd",   OL_VRVRVR,    0b101001),
    InstCOP2Spec1Type("vmul",    OL_VRVRVR,    0b101010),
    InstCOP2Spec1Type("vmax",    OL_VRVRVR,    0b101011),
    InstCOP2Spec1Type("vsub",    OL_VRVRVR,    0b101100),
    InstCOP2Spec1Type("vmsub",   OL_VRVRVR,    0b101101),
    InstCOP2Spec1Type("vopmsub", OL_VRVRVR,    0b101110),
    InstCOP2Spec1Type("vmini",   OL_VRVRVR,    0b101111),
    InstCOP2Spec1Type("viadd",   OL_VRVRVR,    0b110000),
    InstCOP2Spec1Type("visub",   OL_VRVRVR,    0b110001),
    InstCOP2Spec1Type("viaddi",  OL_VRVRVR,     0b110010),
    InstNop, //                             0b110011
    InstCOP2Spec1Type("viand",   OL_VRVRVR,    0b110100),
    InstCOP2Spec1Type("vior",    OL_VRVRVR,    0b110101),
    InstNop, //                             0b110110
    InstNop, //                             0b110111
    InstCOP2Spec1Type("vcallms", OL_TARGET, 0b111000),
    InstCOP2Spec1Type("vcallmsr",OL_R,      0b111001),
    InstNop, //                             0b111010
    InstNop, //                             0b111011
    InstNop, //                             0b111100
    InstNop, //                             0b111101
    InstNop, //                             0b111110
    InstNop, //                             0b111111
};

MipsInstruction g_MipsInstructionsCOP2S2[] = {
    InstCOP2Spec2Type("vaddax",   OL_AVRVR,   0b0000000),
    InstCOP2Spec2Type("vadday",   OL_AVRVR,   0b0000001),
    InstCOP2Spec2Type("vaddaz",   OL_AVRVR,   0b0000010),
    InstCOP2Spec2Type("vaddaw",   OL_AVRVR,   0b0000011),
    InstCOP2Spec2Type("vsubax",   OL_AVRVR,   0b0000100),
    InstCOP2Spec2Type("vsubay",   OL_AVRVR,   0b0000101),
    InstCOP2Spec2Type("vsubaz",   OL_AVRVR,   0b0000110),
    InstCOP2Spec2Type("vsubaw",   OL_AVRVR,   0b0000111),
    InstCOP2Spec2Type("vmaddax",  OL_AVRVR,   0b0001000),
    InstCOP2Spec2Type("vmadday",  OL_AVRVR,   0b0001001),
    InstCOP2Spec2Type("vmaddaz",  OL_AVRVR,   0b0001010),
    InstCOP2Spec2Type("vmaddaw",  OL_AVRVR,   0b0001011),
    InstCOP2Spec2Type("vmsubax",  OL_AVRVR,   0b0001100),
    InstCOP2Spec2Type("vmsubay",  OL_AVRVR,   0b0001101),
    InstCOP2Spec2Type("vmsubaz",  OL_AVRVR,   0b0001110),
    InstCOP2Spec2Type("vmsubaw",  OL_AVRVR,   0b0001111),
    InstCOP2Spec2Type("vitof0",   OL_VRVR,   0b0010000),
    InstCOP2Spec2Type("vitof4",   OL_VRVR,   0b0010001),
    InstCOP2Spec2Type("vitof12",  OL_VRVR,   0b0010010),
    InstCOP2Spec2Type("vitof15",  OL_VRVR,   0b0010011),
    InstCOP2Spec2Type("vftoi0",   OL_VRVR,   0b0010100),
    InstCOP2Spec2Type("vftoi4",   OL_VRVR,   0b0010101),
    InstCOP2Spec2Type("vftoi12",  OL_VRVR,   0b0010110),
    InstCOP2Spec2Type("vftoi15",  OL_VRVR,   0b0010111),
    InstCOP2Spec2Type("vmulax",   OL_AVRVR,   0b0011000),
    InstCOP2Spec2Type("vmulay",   OL_AVRVR,   0b0011001),
    InstCOP2Spec2Type("vmulaz",   OL_AVRVR,   0b0011010),
    InstCOP2Spec2Type("vmulaw",   OL_AVRVR,   0b0011011),
    InstCOP2Spec2Type("vmulaq",   OL_AVRVR,    0b0011100),
    InstCOP2Spec2Type("vabs",     OL_VRVR,   0b0011101),
    InstCOP2Spec2Type("vmulai",   OL_AVRVR,    0b0011110),
    InstCOP2Spec2Type("vclipw",   OL_VRVR,   0b0011111),
    InstCOP2Spec2Type("vaddaq",   OL_AVRVR,    0b0100000),
    InstCOP2Spec2Type("vmaddaq",  OL_AVRVR,    0b0100001),
    InstCOP2Spec2Type("vaddai",   OL_AVRVR,    0b0100010),
    InstCOP2Spec2Type("vmaddai",  OL_AVRVR,    0b0100011),
    InstCOP2Spec2Type("vsubaq",   OL_AVRVR,    0b0100100),
    InstCOP2Spec2Type("vmsubaq",  OL_AVRVR,    0b0100101),
    InstCOP2Spec2Type("vsubai",   OL_AVRVR,    0b0100110),
    InstCOP2Spec2Type("vmsubai",  OL_AVRVR,    0b0100111),
    InstCOP2Spec2Type("vadda",    OL_AVRVR,   0b0101000),
    InstCOP2Spec2Type("vmadda",   OL_AVRVR,   0b0101001),
    InstCOP2Spec2Type("vmula",    OL_AVRVR,   0b0101010),
    InstNop, //                            0b0101011
    InstCOP2Spec2Type("vsuba",    OL_AVRVR,   0b0101100),
    InstCOP2Spec2Type("vmsuba",   OL_AVRVR,   0b0101101),
    InstCOP2Spec2Type("vopmula",  OL_AVRVR,   0b0101110),
    InstCOP2Spec2Type("vnop",     OL_NONE, 0b0101111),
    InstCOP2Spec2Type("vmove",    OL_VRVR,   0b0110000),
    InstCOP2Spec2Type("vmr32",    OL_VRVR,   0b0110001),
    InstNop, //                            0b0110010
    InstNop, //                            0b0110011
    InstCOP2Spec2Type("vlqi",     OL_VRVR,   0b0110100),
    InstCOP2Spec2Type("vsqi",     OL_VRVR,   0b0110101),
    InstCOP2Spec2Type("vlqd",     OL_VRVR,   0b0110110),
    InstCOP2Spec2Type("vsqd",     OL_VRVR,   0b0110111),
    InstCOP2Spec2Type("vdiv",     OL_VRVR,   0b0111000),
    InstCOP2Spec2Type("vsqrt",    OL_VRVR,   0b0111001),
    InstCOP2Spec2Type("vrsqrt",   OL_VRVR,   0b0111010),
    InstCOP2Spec2Type("vwaitq",   OL_NONE, 0b0111011),
    InstCOP2Spec2Type("vmtir",    OL_VRVR,   0b0111100),
    InstCOP2Spec2Type("vmfir",    OL_VRVR,   0b0111101),
    InstCOP2Spec2Type("vilwr",    OL_VRVR,   0b0111110),
    InstCOP2Spec2Type("viswr",    OL_VRVR,   0b0111111),
    InstCOP2Spec2Type("vrnext",   OL_VRVR,   0b1000000),
    InstCOP2Spec2Type("vrget",    OL_VRVR,   0b1000001),
    InstCOP2Spec2Type("vrinit",   OL_VRVR,   0b1000010),
    InstCOP2Spec2Type("vrxor",    OL_VRVR,   0b1000011),
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
