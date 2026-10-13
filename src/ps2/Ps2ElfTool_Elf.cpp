#include "Ps2ElfTool_Elf.h"

Elf::Elf()
{
    this->failed = false;
}
Elf::Elf(ByteArray data) 
{
    this->failed = false;
    LoadData(data);
}
Elf::Elf(File elffile)
{
    this->failed = false;
    LoadFile(elffile);
}

void Elf::LoadData(ByteArray data)
{
    u32* ptr = (u32*)data.Cptr();
    if (*ptr != 0x464C457F) {
        this->failed = true;
        return;
    }
    NCopy(&this->header, data.Cptr(), sizeof(ElfEhdr));
    this->sections = Array<ElfSection>(header.numSectHdrs);
    u8* sectHdrData = data.Cptr() + header.offsetSectHdr;
    for (int i = 0; i < header.numSectHdrs; i++) {
        NCopy(&sections[i].header, sectHdrData + (i * header.sizeSectHdrEnt), header.sizeSectHdrEnt);
    }
    u8* strtbl = data.Cptr() + sections[header.stringTableIdx].header.offsetData;
    for (int i = 0; i < header.numSectHdrs; i++) {
        sections[i].name = String((char*)strtbl + sections[i].header.offsetStrTbl);
        if (sections[i].header.type == SHT_NOBITS) {
            sections[i].data = ByteArray(sections[i].header.sizeData);
            NZero(sections[i].data.Cptr(), sections[i].header.sizeData);
        }
        else
            sections[i].data = ByteArray(data.Cptr() + sections[i].header.offsetData, sections[i].header.sizeData);
    }
}
void Elf::LoadFile(File elffile)
{
    if (!elffile.IsOpen()) {
        elffile.Open(elffile.Path(), FOM_READ);
    }

    ByteArray data = elffile.Read(sizeof(ehdr));
    u32* ptr = (u32*)data.Cptr();
    if (*ptr != 0x464C457F) {
        this->failed = true;
        return;
    }

    NCopy(&header, data.Cptr(), sizeof(ehdr));

    sections = Array<ElfSection>(header.numSectHdrs);

    elffile.Seek(header.offsetSectHdr, SEEK_SET);
    for (int i = 0; i < sections.Size(); i++) {
        ByteArray sdata = elffile.Read(header.sizeSectHdrEnt);
        NCopy(&sections[i], sdata.Cptr(), header.sizeSectHdrEnt);
    }

    elffile.Seek(sections[header.stringTableIdx].header.offsetData, SEEK_SET);

    ByteArray stdata = elffile.Read(sections[header.stringTableIdx].header.sizeData);

    for (int i = 0; i < sections.Size(); i++) {
        int idx = sections[i].header.offsetStrTbl;
        sections[i].name = String((char*)stdata.Cptr() + idx);
        elffile.Seek(sections[i].header.offsetData, SEEK_SET);
        sections[i].data = elffile.Read(sections[i].header.sizeData);
    }
}

bool Elf::Failed() { return this->failed; }

Array<String> Elf::SectionNames()
{
    Array<String> out(sections.Size());
    for (int i = 0; i < sections.Size(); i++) {
        out[i] = sections[i].name;
    }
    return out;
}
String Elf::GetSectionName(int idx)
{
    return sections[idx].name;
}
ElfSection Elf::GetSection(int idx)
{
    return sections[idx];
}
ElfSection Elf::GetSection(String name)
{
    for (int i = 0; i < sections.Size(); i++) {
        if (name == sections[i].name) return sections[i];
    }
    ElfSection e;
    return e;
}
ByteArray Elf::GetSectionData(int idx)
{
    return sections[idx].data;
}
ByteArray Elf::GetSectionData(String name)
{
    for (int i = 0; i < sections.Size(); i++) {
        if (name == sections[i].name) {
            return sections[i].data;
        }
    }
    return ByteArray();
}

u32 Elf::SectionCount() { return sections.Size(); }
