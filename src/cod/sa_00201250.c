#include "godhand/cCoreSave.h"

__attribute__((section(".text.func_00201250")))
void func_00201250(char *a0)
{
    int i = 0;

    if (*(int *)(a0 + 4) != 0)
        goto set;
loop:
    i++;
    if (i >= 0x20)
        return;
    if (*(int *)(a0 + i * 0x88 + 4) == 0)
        goto loop;
set:
    *(int *)(a0 + 0x1108) = 1;
}

