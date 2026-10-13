#ifndef PS2ELFTOOL_CONSOLE_H
#define PS2ELFTOOL_CONSOLE_H

#include "Ps2ElfTool_String.h"

class Console {

public:
    static void Print(String str);
    static void PrintLine(String str);
    static void Printf(String fmt, ...);

private:

};

#endif // PS2ELFTOOL_CONSOLE_H
