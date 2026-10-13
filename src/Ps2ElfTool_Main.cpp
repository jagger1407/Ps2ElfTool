#include "Ps2ElfTool_Main.h"

const char* g_HelpText[] = {
    "Syntax: Ps2ElfTool <command> [options]\n\n"
    "Available commands:\n"
    "section list    - lists all sections of an ELF file.\n"
    "section info    - lists the info of a particular section.\n"
    "section export  - exports the section as binary data.\n"
    "section disasm  - exports the section as assembly code.\n\n"
    "Options:\n"
    "-h / --help     - Shows a helptext describing how to use a command.\n"
    "-i / --input    - Specifies the input file.\n"
    "-o / --output   - Redirects the output into a file.\n"
    "-S / --section  - Selects the ELF section.\n"
    "-l / --location - For 'section export' and 'section disasm',\n"
    "                  specifies a starting offset in the section.\n"
    "-s / --size     - For 'section export' and 'section disasm',\n"
    "                  specifies the size (in bytes) to export / disassemble.\n"
    "-r / --range    - For 'section export' and 'section disasm',\n"
    "                  specifies a range (location,size).\n"
    "                  Combines --location and --size.\n",
    
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

    "Syntax: Ps2ElfTool section disasm [-i|--input] <ELF filepath> <section name> [options]\n"
    "Exports a section within the ELF file as assembly code.\n",

    "Syntax: Ps2ElfTool ldgen [-i|--input] <ELF filepath> [-o|--output]\n"
    "Generates a linker script which reassembles each section back into an ELF.\n",

    "Syntax: Ps2ElfTool disasm [-i|--input] <ELF filepath> [-o|--output] <Project directory>\n"
    "Generates a project folder which disassembles the ELF into its components."
};

Ps2ElfTool::Ps2ElfTool(Array<String> args) : args(&args)
{
    this->argarr = args;
}

int Ps2ElfTool::Run()
{
    RunType t = args.Type();
    if (args.Help()) {
        return PrintHelp(t);
    }

    if(!infile.Open(args.PathInput(), FOM_READ)) {
        Console::Printf("ERROR: File '%s' couldn't be opened.\n", args.PathInput().Cstr());
        return 2;
    }
    ByteArray elfdata = infile.Read(READ_ALL);
    elf.LoadData(elfdata);
    if (elf.Failed()) {
        Console::Printf("ERROR: File '%s' is not a valid ELF File.\n", infile.FileName().Cstr());
        return 2;
    }

    if (!args.PathOutput().IsEmpty()) {
        this->outfile.Open(args.PathOutput(), FOM_WRITE);
        if (!this->outfile.IsOpen()) {
            Console::Printf("ERROR: File '%s' couldn't be opened.\n", args.PathOutput().Cstr());
            return 3;
        }
    }

    switch (args.Type()) {
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

void Ps2ElfTool::Print(String str)
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
    String header = "Name                Address       Size";
    Print(header);
    String line   = "                                  ";
    for (int i = 0; i < scnt; i++) {
        ElfSection section = elf.GetSection(i);
        String name = section.name;
        if (name.IsEmpty()) continue;
        String addr = String::Format("0x%08x", section.header.address);
        String size = String::Format("%d", section.header.sizeData);
        String curLine = line;
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
    String sname = args.Section();
    ElfSection section = elf.GetSection(sname);
    if (section.name.IsEmpty()) {
        Console::Printf("ERROR: Section '%s' couldn't be found.", sname.Cstr());
        return 2;
    }
    Print(String::Format("Information of section %s:", sname.Cstr()));
    Print("Name:      \"" + section.name + "\"");
    Print("Address:   " + String::Format("0x%08x", section.header.address));
    Print("Offset:    " + String::Format("0x%08x", section.header.offsetData));
    Print("Size:      " + String::Format("0x%08x", section.header.sizeData));
    Print("Alignment: " + String::Format("%d", section.header.addralign));
    String tstr;
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
    if(!outfile.IsOpen()) {
        Console::PrintLine("ERROR: section export requires an output file.");
        return 1;
    }
    String sname = args.Section();
    ElfSection section = elf.GetSection(sname);
    if (section.name.IsEmpty()) {
        Console::Printf("ERROR: Section '%s' couldn't be found.", sname.Cstr());
        return 2;
    }
    ByteArray sectionData = elf.GetSectionData(sname);
    u32 start = args.StartLocation();
    u32 length = args.Range();
    if(length == 0) {
        outfile.Write(sectionData);
    }
    else {
        ByteArray range = ByteArray(sectionData.Cptr() + start, length);
        outfile.Write(range);
    }
    return 0;
}
int Ps2ElfTool::SectionDisasm()
{
    String sname = args.Section();
    ElfSection section = elf.GetSection(sname);
    if (section.name.IsEmpty()) {
        Console::Printf("ERROR: Section '%s' couldn't be found.", sname.Cstr());
        return 2;
    }
    Console::Printf("# Disassembling Section %s\n", sname.Cstr());
    ByteArray sectionData = elf.GetSectionData(sname);
    u32 start = args.StartLocation();
    u32 length = args.Range();
    if(length == 0)
        length = sectionData.Size();

    if( start < section.header.address ||
        start > (section.header.address + section.header.sizeData)) {
        Console::Printf("ERROR: Address 0x%08x is outside the range of this section.\n", start);
        return 3;
    }

    ByteArray range = sectionData.Subarray(start - section.header.address, length);
    decoder.LoadData(range, start);

    decoder.Parse();
    Console::PrintLine("# INFO: Section parsed.");
    List<String> lines = decoder.GetAsm();
    Console::PrintLine("# INFO: Section disassembled.");

    for (int i = 0; i < lines.Size(); i++) {
        Print(lines[i]);
    }

    Console::PrintLine("# INFO: Section disassembly fully written.");

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
    Array<String> args(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = String(argv[i]);
    }
    Ps2ElfTool pet(args);

    return pet.Run();
}
