#include "Ps2ElfTool_Registers.h"

char* g_MipsRegistersGP[32] = {
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "a4",   "a5", "a6", "a7", "t0", "t1", "t2", "t3",
    "s0",   "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8",   "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

char* g_MipsRegistersFP[32] = {
    "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",
    "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",
    "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",
    "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31"
};

char* g_MipsRegistersVFP[32] = {
    "vf0", "vf1", "vf2", "vf3", "vf4", "vf5", "vf6", "vf7",
    "vf8", "vf9", "vf10", "vf11", "vf12", "vf13", "vf14", "vf15",
    "vf16", "vf17", "vf18", "vf19", "vf20", "vf21", "vf22", "vf23",
    "vf24", "vf25", "vf26", "vf27", "vf28", "vf29", "vf30", "vf31"
};

char* g_MipsRegistersCOP0[32] = {
    "Index", "Random", "EntryLo0", "EntryLo1", "Context", "PageMask", "Wired", "res7",
    "BadVAddr", "Count", "EntryHi", "Compare", "Status", "Cause", "EPC", "PRId",
    "Config", "res17", "res18", "res19", "res20", "res21", "res22", "BadPAddr",
    "Debug", "Perf", "res26", "res27", "TagLo", "TagHi", "ErrorEPC", "res31"
};

char* g_MipsRegistersCOP1[32] = {
    "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",
    "8",  "9",  "10", "11", "12", "13", "14", "15",
    "16", "17", "18", "19", "20", "21", "22", "23",
    "24", "25", "26", "27", "28", "29", "30", "31"
};

char* g_MipsRegistersCOP2[32] = {
    "vi0",  "vi1",  "vi2",  "vi3",  "vi4",  "vi5",  "vi6",  "vi7",
    "vi8",  "vi9",  "vi10", "vi11", "vi12", "vi13", "vi14", "vi15",
    "status", "mac", "clipping", "r", "i", "q", "res22", "res23",
    "res24", "res25", "res26", "res27", "res28", "res29", "res30", "res31"
};
