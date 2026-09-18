#ifndef MIPSDECODER_H
#define MIPSDECODER_H

#include "../Ps2ElfTool_Common.h"
#include "../util/Ps2ElfTool_ByteArray.h"
#include "../util/Ps2ElfTool_List.h"
#include "../util/Ps2ElfTool_String.h"
#include "Ps2ElfTool_Instructions.h"
#include "Ps2ElfTool_Registers.h"

typedef struct {
    u32 address;
    String8 name;
} AsmLabel;

class MipsDecoder
{
public:
    MipsDecoder();
    MipsDecoder(ByteArray data, u32 start);

    static MipsInstruction DecodeInstruction(u32 instruction);
    static String8 GetInstructionAsm(u32 pc, MipsInstruction* inst);

    void MovePC(u32 address);
    void LoadData(ByteArray data, u32 start);

    int Next();
    void MoveToStart();

    bool AtEnd();

    void Parse();
    List<String8> GetAsm();

    void CreateLabel(u32 address, String8 name);

    u32 GetCurrentInstBytes();

    MipsInstruction Decode();
    String8 GetCurrentAsm();

private:
    ByteArray data;
    List<AsmLabel> labels;
    u32* ip;

    u32 pc;
    u32 start;

    s64 findLabel(u32 address);
};

#endif
