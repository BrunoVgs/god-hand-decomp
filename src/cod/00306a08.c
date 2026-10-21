#include "godhand/cCoreSave.h"

extern int func_003069A8(int a0, unsigned int a1, int *a2);

__attribute__((section(".text.func_00306A08")))
int func_00306A08(char *a0, unsigned int a1, int *a2)
{
    *a2 = 0;
    a0 = a0 + *(int *)(a0 + 0xC);
    if (a1 >= *(unsigned int *)(a0 + 4))
        return 0;
    a1 = func_003069A8((int)a0, a1, a2);
    return a1;
}
