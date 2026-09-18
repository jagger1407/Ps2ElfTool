#include "Ps2ElfTool_ArgReader.h"

#define ARGFLAG(a1, a2) { { a1, a2 }, false, false, "" }
#define ARGVAL(a1, a2)  { { a1, a2 }, false, true,  "" }

Argument g_Args[] = {
	ARGFLAG("-v", "--version"),
	ARGFLAG("-h", "--help"),
	ARGVAL("-i", "--input"),
	ARGVAL("-o", "--output"),
	ARGVAL("-r", "--range")
};

ArgReader::ArgReader()
{
	this->failed = false;
}
ArgReader::ArgReader(Array<String8> args)
{
	this->failed = false;
	if (args.Size() < 2) {
		g_Args[ARG_HELP].enabled = true;
		this->type = RUN_NONE;
		return;
	}
	int curArg = 1;
	String8 cmd1 = args[curArg].ToLower();
	if (cmd1 == "ldgen") {
		this->type = RUN_LDGEN;
	}
	else if (cmd1 == "disasm") {
		this->type = RUN_DISASM;
	}
	else if (cmd1 == "section") {
		if (args.Size() < 3) {
			this->failed = true;
			this->failMsg = "command 'section' needs a second identifier.";
			return;
		}
		curArg++;
		String8 cmd2 = args[curArg].ToLower();
		if (cmd2 == "list") {
			this->type = RUN_SECTION_LIST;
		}
		else if (cmd2 == "info") {
			this->type = RUN_SECTION_INFO;
		}
		else if (cmd2 == "export") {
			this->type = RUN_SECTION_EXPORT;
		}
		else if (cmd2 == "disasm") {
			this->type = RUN_SECTION_DISASM;
		}
		else {
			this->failed = true;
			this->failMsg = String8::Format("Unknown command 'section %s'.", cmd2.Cstr());
			return;
		}
		curArg++;
	}

	if (!args[curArg].StartsWith("-")) {
		g_Args[ARG_INPUT].enabled = true;
		g_Args[ARG_INPUT].value = args[curArg++];
		if (this->type == RUN_SECTION_INFO ||
			this->type == RUN_SECTION_EXPORT ||
			this->type == RUN_SECTION_DISASM) {

			if (curArg >= args.Size()) {
				this->failed = true;
				this->failMsg = "Section commands require the section name.";
				return;
			}
			g_Args[ARG_INPUT].value += ";" + args[curArg++];
		}
	}

	for (; curArg < args.Size(); curArg++) {
		for (int i = 0; i < ARRLEN(g_Args); i++) {
			if (args[curArg] == g_Args[i].arg[0] || args[curArg] == g_Args[i].arg[1]) {
				g_Args[i].enabled = true;
				if (g_Args[i].hasValue) {
					if (curArg+1 < args.Size()) {
						curArg++;
						g_Args[i].value = args[curArg];
					}
					else {
						this->failed = true;
						this->failMsg = String8::Format("Option %s/%s needs a value.", g_Args[i].arg[0].Cstr(), g_Args[i].arg[1].Cstr());
						return;
					}
				}
			}
		}
	}
}

Argument ArgReader::GetArg(ArgumentType type)
{
	return g_Args[type];
}

RunType ArgReader::GetRunType() { return this->type; }

bool ArgReader::Failed() { return this->failed; }

String8 ArgReader::GetFailMessage() { return this->failMsg; }
