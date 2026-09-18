#include "Ps2ElfTool_Common.h"

void NCopy(void* dest, void* src, u64 size)
{
    if (dest == nullptr || src == nullptr) return;
    u8* dptr = (u8*)dest;
    u8* sptr = (u8*)src;
    for (int i = 0; i < size; ++i) {
        dptr[i] = sptr[i];
    }
}

bool NCompare(u8* ptr1, u8* ptr2, u64 size)
{
    if(ptr1 == nullptr) {
        if(ptr2 == nullptr) return true;
        return false;
    }
    if(ptr2 == nullptr) return false;

    for(u64 i=0;i<size;++i) {
        if(ptr1[i] != ptr2[i]) return false;
    }

    return true;
}

void NZero(void* ptr, u64 size)
{
    u8* tmp = (u8*)ptr;
    for (u64 i = 0; i < size; i++) {
        tmp[i] = 0x00;
    }
}

