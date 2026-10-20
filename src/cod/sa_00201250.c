/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_00201250, split from src/cod/batch28_nm.c by the NM closer. */
#include "godhand/cCoreSave.h"

extern int D_0076A7AC;
extern void (*D_003F2810[])(int);
extern unsigned char D_007474A0[];
typedef struct { int a; int b; } Pair28;
extern Pair28 D_007558A8[];

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

