#ifndef MIPSDECODER_H
#define MIPSDECODER_H

#include "../Ps2ElfTool_Common.h"
#include "../util/Ps2ElfTool_ByteArray.h"
#include "../util/Ps2ElfTool_List.h"
#include "../util/Ps2ElfTool_String.h"
#include "Ps2ElfTool_Instructions.h"
#include "Ps2ElfTool_Registers.h"

typedef enum : u8 {
    LBL_NONE,
    LBL_LAB,
    LBL_FUN,
    LBL_DAT
} LabelState;

class MipsDecoder
{
public:
    MipsDecoder();
    MipsDecoder(ByteArray data, u32 start);

    void LoadData(ByteArray data, u32 start);

    void MoveToStart();
    u32 Next();
    bool AtEnd();

    void AnalyzeLabels();

    List<String> GetAsm();

    static void DecodeInstruction(MipsInstruction* inst, u32 instruction);
    static String GetInstructionAsm(MipsInstruction* inst, u32 pc);

private:
    ByteArray data;
    ByteArray lbls;
    u32* ip;
    u32 pc;
    u32 start;
};

#endif
