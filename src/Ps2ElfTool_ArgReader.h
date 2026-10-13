#ifndef INTERFACE_H
#define INTERFACE_H

#include "Ps2ElfTool_Common.h"

#include "util/Ps2ElfTool_Array.h"
#include "util/Ps2ElfTool_String.h"

typedef enum {
	RUN_ERROR,
	RUN_SECTION_LIST,
	RUN_SECTION_INFO,
	RUN_SECTION_EXPORT,
	RUN_SECTION_DISASM,
	RUN_LDGEN,
	RUN_DISASM,
} RunType;

class ArgReader {
public:
	ArgReader(Array<String>* args);

	bool Help();
	String PathInput();
	String PathOutput();
	String Section();
	u32 StartLocation();
	u32 Range();
	RunType Type();
	String TypeString();

private:
	bool help;
	String inputpath;
	String outputpath;
	String section;
	u32 location;
	u32 size;
	RunType type;
};

#endif
