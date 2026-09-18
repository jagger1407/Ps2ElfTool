#include "Ps2ElfTool_Console.h"

void Console::Print(String8 str)
{
    printf("%s", str.Cstr());
}

void Console::PrintLine(String8 str)
{
    puts(str.Cstr());
}

void Console::Printf(String8 fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    vprintf(fmt.Cstr(), args);

    va_end(args);
}
