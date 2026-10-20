#include "godhand/mwsfViews.h"

__attribute__((section(".text.func_00345250")))
int func_00345250(MwRing *r)
{
    int i = r->pos % 8;

    if (r->ent[i].stat != 1)
        return 0;
    return r->ent[i].val;
}

