#include "Ps2ElfTool_Main.h"

const char* g_HelpText[] = {
    "Syntax: Ps2ElfTool <command> [options]\n\n"
    "Available commands:\n"
    "section list   - lists all sections of an ELF file.\n"
    "section info   - lists the info of a particular section.\n"
    "section export - exports the section as binary data.\n"
    "section disasm - exports the section as assembly code.\n\n"
    "Options:\n"
    "-h / --help    - Shows a helptext describing how to use a command.\n"
    "-v / --verbose - Prints execution information to the console.\n"
    "                 Can only be used when --output option is given."
    "-i / --input   - Specifies the input file.\n"
    "-o / --output  - Redirects the output into a file.\n"
    "-r / --range   - For 'section export' and 'section disasm',\n"
    "                 specifies a range (offset,size).\n",
    
    "Syntax: Ps2ElfTool section list [-i|--input] <ELF filepath> [options]\n"
    "Lists each section of the ELF file.\n"
    "Format:\n"
    "Name    - Name of the section\n"
    "Address - Virtual memory load address\n"
    "Size    - Section size in bytes\n",

    "Syntax: Ps2ElfTool section info [-i|--input] <ELF filepath> <section name> [options]\n"
    "Shows the detailed information of a section within the ELF file.\n"
    "Format:\n"
    "Name      - Name of the section\n"
    "Address   - Virtual memory load address\n"
    "Offset    - File offset inside the ELF file\n"
    "Size      - Section size in bytes\n",
    "alignment - Address alignment requirement in bytes\n"
    "Type      - Section type\n",

    "Syntax: Ps2ElfTool section export [-i|--input] <ELF filepath> <section name> [options]\n"
    "Exports a section within the ELF file as binary data.\n",

    "Syntax: Ps2ElfTool section export [-i|--input] <ELF filepath> <section name> [options]\n"
    "Exports a section within the ELF file as assembly code.\n",

    "Syntax: Ps2ElfTool ldgen [-i|--input] <ELF filepath> [-o|--output]\n"
    "Generates a linker script which reassembles each section back into an ELF.\n",

    "Syntax: Ps2ElfTool disasm [-i|--input] <ELF filepath> [-o|--output] <Project directory>\n"
    "Generates a project folder which disassembles the ELF into its components."
};

Ps2ElfTool::Ps2ElfTool(Array<String8> args)
{
    this->argarr = args;
    this->args = ArgReader(argarr);
}

int Ps2ElfTool::Run()
{
    if (args.Failed()) {
        Console::PrintLine("ERROR: " + this->args.GetFailMessage());
        return 1;
    }

    RunType t = args.GetRunType();
    Argument help = args.GetArg(ARG_HELP);
    if (help.enabled) {
        return PrintHelp(t);
    }

    File f(args.GetArg(ARG_INPUT).value.Split(";")[0], FOM_READ);
    ByteArray elfdata = f.Read(READ_ALL);
    elf.LoadData(elfdata);
    if (elf.Failed()) {
        Console::Printf("ERROR: File '%s' is not a valid ELF File.", f.FileName().Cstr());
        return 2;
    }

    if (args.GetArg(ARG_OUTPUT).enabled) {
        this->outfile = File(args.GetArg(ARG_OUTPUT).value, FOM_WRITE);
        if (!this->outfile.IsOpen()) {
            Console::Printf("ERROR: File '%s' couldn't be opened.\n", args.GetArg(ARG_OUTPUT).value.Cstr());
            return 3;
        }
    }

    switch (args.GetRunType()) {
    case RUN_SECTION_LIST: {
        return SectionList();
    } break;
    case RUN_SECTION_INFO: {
        return SectionInfo();
    } break;
    case RUN_SECTION_EXPORT: {
        return SectionExport();
    } break;
    case RUN_SECTION_DISASM: {
        return SectionDisasm();
    } break;
    case RUN_LDGEN: {
        return LdGen();
    } break;
    case RUN_DISASM: {
        return ElfDisasm();
    } break;
    default: {
        Console::PrintLine("ERROR: Invalid command.");
        return 1;
    } break;
    }

    return 0;
}

int Ps2ElfTool::PrintHelp(RunType type)
{
    Console::PrintLine(g_HelpText[type]);
    return 0;
}

void Ps2ElfTool::Print(String8 str)
{
    if (!outfile.IsOpen()) {
        Console::PrintLine(str);
    }
    else {
        outfile.WriteLine(str);
    }
}

int Ps2ElfTool::SectionList()
{
    int scnt = elf.SectionCount();
    if (scnt <= 0) {
        Console::PrintLine("ERROR: This ELF file does not have any sections.");
        return 2;
    }
    String8 header = "Name                Address       Size";
    Print(header);
    String8 line   = "                                  ";
    for (int i = 0; i < scnt; i++) {
        ElfSection section = elf.GetSection(i);
        String8 name = section.name;
        if (name.IsEmpty()) continue;
        String8 addr = String8::Format("0x%08x", section.header.address);
        String8 size = String8::Format("%d", section.header.sizeData);
        String8 curLine = line;
        char* ptr = curLine.Cstr();

        if (name.Length() > 16) {
            name = name.Substring(0, 16);
            name += "...";
        }

        NCopy(ptr, name.Cstr(), name.Length());
        NCopy(ptr + 20, addr.Cstr(), addr.Length());
        curLine += size;

        Print(curLine);
    }

    return 0;
}
int Ps2ElfTool::SectionInfo()
{
    String8 sname = args.GetArg(ARG_INPUT).value.Split(";")[1];
    ElfSection section = elf.GetSection(sname);
    if (section.name.IsEmpty()) {
        Console::Printf("ERROR: Section '%s' couldn't be found.", sname.Cstr());
        return 2;
    }
    Print(String8::Format("Information of section %s:", sname.Cstr()));
    Print("Name:      \"" + section.name + "\"");
    Print("Address:   " + String8::Format("0x%08x", section.header.address));
    Print("Offset:    " + String8::Format("0x%08x", section.header.offsetData));
    Print("Size:      " + String8::Format("0x%08x", section.header.sizeData));
    Print("Alignment: " + String8::Format("%d", section.header.addralign));
    String8 tstr;
    if (section.header.type > 0x6FFFFFFF) {
        tstr = EshtNames[section.header.type - 0x70000000];
    }
    else
        tstr = ShtNames[section.header.type];

    Print("Type:      " + tstr);
    return 0;
}
int Ps2ElfTool::SectionExport()
{
    String8 sname = args.GetArg(ARG_INPUT).value.Split(";")[1];
    ElfSection section = elf.GetSection(sname);
    if (section.name.IsEmpty()) {
        Console::Printf("ERROR: Section '%s' couldn't be found.", sname.Cstr());
        return 2;
    }
    ByteArray sectionData = elf.GetSectionData(sname);
    if (args.GetArg(ARG_RANGE).enabled) {
        u32 start = atoi(args.GetArg(ARG_RANGE).value.Split(",")[0].Cstr());
        u32 length = atoi(args.GetArg(ARG_RANGE).value.Split(",")[1].Cstr());
        ByteArray range = ByteArray(sectionData.Cptr() + start, length);
        outfile.Write(range);
    }
    else {
        outfile.Write(sectionData);
    }
    return 0;
}
int Ps2ElfTool::SectionDisasm()
{
    String8 sname = args.GetArg(ARG_INPUT).value.Split(";")[1];
    ElfSection section = elf.GetSection(sname);
    if (section.name.IsEmpty()) {
        Console::Printf("ERROR: Section '%s' couldn't be found.", sname.Cstr());
        return 2;
    }
    Console::Printf("Disassembling Section %s\n", sname.Cstr());
    ByteArray sectionData = elf.GetSectionData(sname);
    if (args.GetArg(ARG_RANGE).enabled) {
        u64 start = args.GetArg(ARG_RANGE).value.Split(",")[0].ToU64();
        u64 length = args.GetArg(ARG_RANGE).value.Split(",")[1].ToU64();

        if(start < section.header.address ||
           start > (section.header.address + section.header.sizeData)) {
            Console::Printf("ERROR: Address 0x%08x is outside the range of this section.\n", start);
            return 3;
        }

        ByteArray range = sectionData.Subarray(start - section.header.address, length);
        decoder.LoadData(range, start);
    }
    else {
        decoder.LoadData(sectionData, section.header.address);
    }
    decoder.Parse();
    Console::PrintLine("INFO: Section parsed.");
    List<String8> lines = decoder.GetAsm();
    Console::PrintLine("INFO: Section disassembled.");
    u64 percent = lines.Size() / 100;
    u32 p = 0;

    for (int i = 0; i < lines.Size(); i++) {
        outfile.WriteLine(lines[i]);
#if 0
        if (i % percent == 0) {
            Console::Printf("%d%% written.\n", p);
            p++;
        }
#endif
    }

    Console::PrintLine("INFO: Section disassembly fully written.");

    return 0;
}

int Ps2ElfTool::LdGen()
{
    Console::PrintLine("Not implemented yet.");
    return 0;
}

int Ps2ElfTool::ElfDisasm()
{
    Console::PrintLine("Not implemented yet.");
    return 0;
}

int main(int argc, char** argv)
{
    Array<String8> args(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = String8(argv[i]);
    }
    Ps2ElfTool pet(args);

    return pet.Run();
}
