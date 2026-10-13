#ifndef PS2ELFTOOL_H
#define PS2ELFTOOL_H

#include "Ps2ElfTool_Common.h"
#include "Ps2ElfTool_ArgReader.h"
#include "util/Ps2ElfTool_Array.h"
#include "util/Ps2ElfTool_String.h"
#include "util/Ps2ElfTool_File.h"
#include "util/Ps2ElfTool_Console.h"
#include "ps2/Ps2ElfTool_Elf.h"
#include "ps2/Ps2ElfTool_MipsDecoder.h"

#define VERSION "1.0.0"

const char* ShtNames[] = {
    "SHT_NULL",
    "SHT_PROGBITS",
    "SHT_SYMTAB",
    "SHT_STRTAB",
    "SHT_RELA",
    "SHT_HASH",
    "SHT_DYNAMIC",
    "SHT_NOTE",
    "SHT_NOBITS",
    "SHT_REL",
    "SHT_SHLIB",
    "SHT_DYNSYM",
};
const char* EshtNames[] = {
    "EST_MIPS_LIBLIST",
    "EST_MIPS_MSYM",
    "EST_MIPS_CONFLICT",
    "EST_MIPS_GPTAB",
    "EST_MIPS_UCODE",
    "EST_MIPS_REGINFO"
};

class Ps2ElfTool {

public:
    Ps2ElfTool(Array<String> args);

    int Run();

    int PrintHelp(RunType type);
    int PrintVersion();

    int SectionList();
    int SectionInfo();
    int SectionExport();
    int SectionDisasm();

    int LdGen();

    int ElfDisasm();

private:
    ArgReader args;
    Array<String> argarr;
    Elf elf;
    MipsDecoder decoder;

    File infile;
    File outfile;

    void Print(String str);
};

#endif // PS2ELFTOOL_H
