/* Batch 26: SN matches (300-byte allocator pair + unique small bodies). */
#include "include_asm.h"
#include "godhand/vu0.h"

/* 300-byte locked allocator + nested VU zero + flag clears.
 * Pair differs only in mask + heap. */

INCLUDE_ASM("nonmatching", func_00317D50);
INCLUDE_ASM("nonmatching", func_003181A8);

/* Unique small SN bodies. */

INCLUDE_ASM("nonmatching", func_0030A538);

INCLUDE_ASM("nonmatching", func_0030A548);

extern int func_00385E98(void *a0);

__attribute__((section(".text.func_0037E8D8")))
int func_0037E8D8(char *self)
{
    int r;

    *(int *)(self + 8) = 0;
    *(int *)(self + 0xC) = 0;
    r = func_00385E98(*(void **)(self + 0x10));
    return r != 0;
}
