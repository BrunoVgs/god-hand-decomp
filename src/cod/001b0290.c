#include "godhand/vu0.h"

extern char *InitFields_1B6E90(char *a0);
extern int D_00428160;

__attribute__((section(".text.func_001B0290")))
void *func_001B0290(void *object)
{
    InitFields_1B6E90((char *)object);
    *(int **)((char *)object + 0x214) = &D_00428160;
    VU0_SQC2_VF0(object, 0x610);
    return object;
}
