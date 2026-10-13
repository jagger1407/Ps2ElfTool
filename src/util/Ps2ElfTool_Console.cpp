#include "Ps2ElfTool_Console.h"

void Console::Print(String str)
{
    printf("%s", str.Cstr());
}

void Console::PrintLine(String str)
{
    puts(str.Cstr());
}

void Console::Printf(String fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    vprintf(fmt.Cstr(), args);

    va_end(args);
}
