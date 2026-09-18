#ifndef PS2ELFTOOL_CONSOLE_H
#define PS2ELFTOOL_CONSOLE_H

#include "Ps2ElfTool_String.h"

class Console {

public:
    static void Print(String8 str);
    static void PrintLine(String8 str);
    static void Printf(String8 fmt, ...);

private:

};

#endif // PS2ELFTOOL_CONSOLE_H
