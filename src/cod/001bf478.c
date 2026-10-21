#include "godhand/cCoreSave.h"

extern char *InitFields_1B6E90(char *a0);
extern int D_004296F0;

__attribute__((section(".text.func_001BF478")))
void *func_001BF478(void *object)
{
    InitFields_1B6E90((char *)object);
    *((char *)object + 0x600) = -1;
    *(int **)((char *)object + 0x214) = &D_004296F0;
    return object;
}
