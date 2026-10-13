#include "Ps2ElfTool_ArgReader.h"

ArgReader::ArgReader(Array<String>* args)
{
    String curArg;
    this->help = false;
    this->inputpath = "";
    this->outputpath = "";
    this->location = 0;
    this->size = 0;
    this->type = RUN_ERROR;

    int iArg = 1;
    curArg = args->Get(iArg);
    iArg++;
    curArg = curArg.ToLower();
    if(curArg == "disasm") {
        this->type = RUN_DISASM;
    }
    else if(curArg == "ldgen") {
        this->type = RUN_LDGEN;
    }
    else if(curArg == "section") {
        curArg = args->Get(iArg);
        iArg++;
        curArg = curArg.ToLower();
        if(curArg == "list") {
            this->type = RUN_SECTION_LIST;
        }
        else if(curArg == "info") {
            this->type = RUN_SECTION_INFO;
        }
        else if(curArg == "export") {
            this->type = RUN_SECTION_EXPORT;
        }
        else if(curArg == "disasm") {
            this->type = RUN_SECTION_DISASM;
        }
    }

    curArg = args->Get(iArg);
    if(!curArg.StartsWith("-")) {
        this->inputpath = curArg;
        iArg++;
    }


    for(int i = iArg;i<args->Size();i++) {
        curArg = args->Get(i);
        if(curArg == "-h" || curArg == "--help") {
            this->help = true;
        }
        else if(curArg == "-i" || curArg == "--input") {
            i++;
            curArg = args->Get(i);
            this->inputpath = curArg;
        }
        else if(curArg == "-o" || curArg == "--output") {
            i++;
            curArg = args->Get(i);
            this->outputpath = curArg;
        }
        else if(curArg == "-S" || curArg == "--section") {
            i++;
            curArg = args->Get(i);
            this->section = curArg;
        }
        else if(curArg == "-l" || curArg == "--location") {
            i++;
            curArg = args->Get(i);
            this->location = curArg.ToU64();
        }
        else if(curArg == "-s" || curArg == "--size") {
            i++;
            curArg = args->Get(i);
            this->size = curArg.ToU64();
        }
        else if(curArg == "-r" || curArg == "--range") {
            i++;
            curArg = args->Get(i);
            Array<String> parts = curArg.Split(",");
            if(parts.Size() != 2) continue;
            this->location = parts[0].ToU64();
            this->size = parts[1].ToU64();
        }
    }
}
bool ArgReader::Help()
{
    return this->help;
}
String ArgReader::PathInput()
{
    return this->inputpath;
}
String ArgReader::PathOutput()
{
    return this->outputpath;
}
u32 ArgReader::StartLocation()
{
    return this->location;
}
u32 ArgReader::Range()
{
    return this->size;
}
String ArgReader::Section()
{
    return this->section;
}

RunType ArgReader::Type()
{
    return this->type;
}

const char* _typestr[] = {
    "RUN_ERROR",
    "RUN_SECTION_LIST",
    "RUN_SECTION_INFO",
    "RUN_SECTION_EXPORT",
    "RUN_SECTION_DISASM",
    "RUN_LDGEN",
    "RUN_DISASM",
};

String ArgReader::TypeString()
{
    return _typestr[this->type];
}
