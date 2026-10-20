/* sn-2.95.3-136: func_0037D310, first free entry in the 24-entry bank holding n
 * (the third bank has only 3 entries). */
#include "godhand/seqNode.h"

__attribute__((section(".text.func_0037D310")))
SeqNode *func_0037D310(signed char n)
{
    SeqNode *e;
    int base, cnt, i;

    base = n / 24 * 24;
    cnt = base == 48 ? 3 : 24;
    for (i = 0; i < cnt; i++) {
        e = &D_0076CF20[base + i];
        if (e->flags == 0)
            return e;
    }
    return 0;
}
