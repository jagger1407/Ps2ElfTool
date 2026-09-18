#ifndef PS2ELFTOOL_COMMON_H
#define PS2ELFTOOL_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstdarg>

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;
typedef int64_t s64;

typedef int8_t char8;
typedef int16_t char16;

#define ARRLEN(x) (sizeof(x) / sizeof(x[0]))

#define REINTERPRET(type, var) *(type*)&var

void NCopy(void* dest, void* src, u64 size);
bool NCompare(u8* ptr1, u8* ptr2, u64 size);
void NZero(void* ptr, u64 size);

#endif // PS2ELFTOOL_COMMON_H
