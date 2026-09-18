#ifndef INTERFACE_H
#define INTERFACE_H

#include "Ps2ElfTool_Common.h"

#include "util/Ps2ElfTool_Array.h"
#include "util/Ps2ElfTool_String.h"

typedef struct {
	String8 arg[2];
	bool enabled;
	bool hasValue;
	String8 value;
} Argument;

typedef enum {
	ARG_VERBOSE,
	ARG_HELP,
	ARG_INPUT,
	ARG_OUTPUT,
	ARG_RANGE
} ArgumentType;

typedef enum {
	RUN_NONE,
	RUN_SECTION_LIST,
	RUN_SECTION_INFO,
	RUN_SECTION_EXPORT,
	RUN_SECTION_DISASM,
	RUN_LDGEN,
	RUN_DISASM
} RunType;

extern Argument g_Args[];

class ArgReader {
public:
	ArgReader();
	ArgReader(Array<String8> args);

	Argument GetArg(ArgumentType type);
	RunType GetRunType();

	bool Failed();
	String8 GetFailMessage();

private:
	bool failed;
	String8 failMsg;

	RunType type;
};

#endif