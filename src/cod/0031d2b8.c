/* sn-2.95.3-136: stage set-data mesh placement (0x31D2B8..). */
#include "godhand/gameWork.h"

#include "godhand/stageSet.h"


__attribute__((section(".text.func_0031D2B8")))
void func_0031D2B8(int a, int b)
{
    D_007558A8[D_007474A0.pairNum].a = a;
    D_007558A8[D_007474A0.pairNum].b = b;
    D_007474A0.pairNum++;
}

__attribute__((section(".text.func_0031D658")))
int func_0031D658(char *grp, unsigned char hide)
{
    int i;
    char *ent;

    for (i = 0; i < *(unsigned short *)(grp + 8); i++) {
        ent = (char *)(((int *)(grp + 0x10))[i] + (int)grp);
        func_0031D3D0((SetData *)ent, *(int *)ent + (int)ent, i, hide);
    }
    return *(unsigned short *)(grp + 8);
}
