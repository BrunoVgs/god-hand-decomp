/* Batch 28: unique SN bodies, smallest first. Matched only. */
#include "godhand/cCoreSave.h"

extern void InitFields_1B6E90(void *object);
extern int D_004296F0;
extern int func_003069A8(int a0, unsigned int a1, int *a2);
extern int D_007479F4;
extern void cPadVib_stopSeq(char *a0);

__attribute__((section(".text.func_001BF478")))
void *func_001BF478(void *object)
{
    InitFields_1B6E90(object);
    __asm__ __volatile__("" : : : "v0");
    *((char *)object + 0x600) = -1;
    *(int **)((char *)object + 0x214) = &D_004296F0;
    return object;
}

__attribute__((section(".text.func_00306A08")))
int func_00306A08(char *a0, unsigned int a1, int *a2)
{
    *a2 = 0;
    a0 = a0 + *(int *)(a0 + 0xC);
    if (a1 >= *(unsigned int *)(a0 + 4))
        return 0;
    a1 = func_003069A8((int)a0, a1, a2);
    __asm__ volatile("");
    return a1;
}
