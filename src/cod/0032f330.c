/* cygnus-2.96: func_0032F330, take a free one of the four 0x1964-byte decoder slots, clear it and
 * copy in n stream handles; returns the slot, or 0 when all four are in use. */
#include "godhand/adxm.h"

extern void *func_003A52F0(void *dst, int c, int n);

__attribute__((section(".text.func_0032F330")))
AdxDecSlot *func_0032F330(int n, int arg, int *h)
{
    AdxDecSlot *s;
    int i;

    for (i = 0; i < 4; i++) {
        if (D_003D1E70[i].used == 0)
            break;
    }
    if (i == 4)
        return 0;
    s = &D_003D1E70[i];
    func_003A52F0(s, 0, sizeof(AdxDecSlot));
    s->unk01 = 0;
    s->arg = arg;
    for (i = 0; i < n; i++)
        s->h[i] = h[i];
    s->n = n;
    s->unk03 = 0;
    s->unk04 = 0;
    s->used = 1;
    return s;
}
