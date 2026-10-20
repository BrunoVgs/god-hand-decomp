/* Batch 26: SN matches (300-byte allocator pair + unique small bodies). */
#include "include_asm.h"
#include "godhand/vu0.h"

extern int D_00747A34;
extern char D_00754C10[];
extern char D_00754220[];
extern int D_0044B528;
extern void *EnsureInitThenForward_2A9538_30EE08(int size, int align, void *region);
extern void func_003A52F0(void *dst, int val, int len);
extern void cObjBase(void *a0);

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
