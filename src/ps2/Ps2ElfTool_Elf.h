#ifndef PS2ELFTOOL_ELF_H
#define PS2ELFTOOL_ELF_H

#include "../Ps2ElfTool_Common.h"
#include "../util/Ps2ElfTool_String.h"
#include "../util/Ps2ElfTool_File.h"

#define ELF_IDENTIFIER 0x464C457F

typedef enum {
    EI_MAGIC,
    EI_BITNESS = 4,
    EI_ENDIAN,
    EI_VERSION,
    EI_OSABI,
    EI_ABIVERSION
} ElfIdentifier;

typedef enum : u16 {
    ET_NONE,
    ET_REL,
    ET_EXEC,
    ET_DYN,
    ET_CORE
} ElfType;

typedef enum : u16 {
    EM_NONE,
    EM_386 = 3,
    EM_MIPS = 8,
    EM_ARM = 40,
    EM_X86_64 = 62,
    EM_AARCH64 = 183
} ElfMachine;

typedef enum : u32 {
    SHT_NULL     = 0,
    SHT_PROGBITS = 1,
    SHT_SYMTAB   = 2,
    SHT_STRTAB   = 3,
    SHT_RELA     = 4,
    SHT_HASH     = 5,
    SHT_DYNAMIC  = 6,
    SHT_NOTE     = 7,
    SHT_NOBITS   = 8,
    SHT_REL      = 9,
    SHT_SHLIB    = 10,
    SHT_DYNSYM   = 11,

    // MIPS Architecture Specific
    EST_MIPS_LIBLIST = 0x70000000,
    EST_MIPS_MSYM    = 0x70000001,
    EST_MIPS_CONFLICT= 0x70000002,
    EST_MIPS_GPTAB   = 0x70000003,
    EST_MIPS_UCODE   = 0x70000004,
    EST_MIPS_REGINFO = 0x70000006
} ElfSectionType;

// Main ELF File Header
typedef struct ehdr {
    u8  identifier[16];

    ElfType type;       // Object file type
    ElfMachine machine; // Architecture (0x08 for MIPS)
    u32 version;        // Object file version
    u32 entrypoint;     // Virtual address entry point
    u32 offsetProgHdr;  // Program header table file offset
    u32 offsetSectHdr;  // Section header table file offset
    u32 flags;          // Processor-specific flags
    u16 sizeHdr;        // ELF header size in bytes (usually 52)
    u16 sizeProgHdrEnt; // Size of one program header entry
    u16 numProgHdrs;    // Number of program headers
    u16 sizeSectHdrEnt; // Size of one section header entry (usually 40)
    u16 numSectHdrs;    // Number of section headers
    u16 stringTableIdx; // Section header string table index
} ElfEhdr;

// Section Header
typedef struct shdr {
    u32 offsetStrTbl;    // String table offset for name
    ElfSectionType type; // Section type (SHT_PROGBITS, SHT_SYMTAB, etc.)
    u32 flags;           // Section attribute flags
    u32 address;         // RAM Address in PS2 memory
    u32 offsetData;      // File offset to section raw data
    u32 sizeData;        // Section size in bytes
    u32 link;            // Link to another section
    u32 info;            // Additional section information
    u32 addralign;       // Address alignment constraints
    u32 sizeEnt;         // Size of entries if section holds a table
} ElfShdr;

typedef struct esect {
    String8 name;
    ElfShdr header;
    ByteArray data;
} ElfSection;

class Elf {

public:
    Elf();
    Elf(ByteArray data);
    Elf(File elffile);

    void LoadData(ByteArray data);
    void LoadFile(File elffile);

    Array<String8> SectionNames();
    String8 GetSectionName(int idx);
    ElfSection GetSection(int idx);
    ElfSection GetSection(String8 name);
    ByteArray GetSectionData(int idx);
    ByteArray GetSectionData(String8 name);

    u32 SectionCount();
    bool Failed();

private:
    ElfEhdr header;
    bool failed;

    Array<ElfSection> sections;
};

#endif // PS2ELFTOOL_ELF_H
