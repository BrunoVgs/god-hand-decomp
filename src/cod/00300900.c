#include "godhand/vu0.h"

extern int D_00741940[];
extern int D_00741960[];
extern int D_00741980[];
extern unsigned char D_0071B940[];
extern void func_00302918(void *p);

__attribute__((section(".text.KillEventEmitter")))
void KillEventEmitter(void)
{
    int i;
    unsigned int mask;
    int w;
    char *p;
    unsigned int top;
    int skip;

    for (i = 0, top = 0x80000000u, skip = 0xD7; i < 0x100; i++) {
        w = (unsigned int)i >> 5;
        mask = top >> (i & 0x1F);
        if ((D_00741940[w] & mask) == 0)
            goto next;
        if ((D_00741960[w] & mask) != 0)
            goto next;
        if ((D_00741980[w] & mask) != 0)
            goto next;
        p = (char *)D_0071B940 + i * 0x260;
        if ((*(int *)(p + 0x118) & 2) == 0)
            goto next;
        if (*(short *)(p + 0x18C) == skip)
            goto next;
        func_00302918(p);
next:
        ;
    }
}
