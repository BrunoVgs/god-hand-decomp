/* sn-2.95.3-136 matched 56-byte Phase A functions. */
#include "godhand/vu0.h"

extern void InitFields_1B6E90(void *object);
extern int D_00428160;
extern int D_00428588;

__attribute__((section(".text.func_001B0290")))
void *func_001B0290(void *object)
{
    InitFields_1B6E90(object);
    __asm__ __volatile__("" : : : "v0");
    *(int **)((char *)object + 0x214) = &D_00428160;
    VU0_SQC2_VF0(object, 0x610);
    return object;
}

__attribute__((section(".text.func_001B24E8")))
void *func_001B24E8(void *object)
{
    InitFields_1B6E90(object);
    __asm__ __volatile__("" : : : "v0");
    *(int **)((char *)object + 0x214) = &D_00428588;
    VU0_SQC2_VF0(object, 0x610);
    return object;
}
