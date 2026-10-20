/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
/* cygnus-2.96 (drop-reorder): func_00356E98, split from src/cod/sa_nm_00345250.c by the NM closer. */

#include "godhand/mwsfViews.h"

extern int func_00356358(SfdWkT *w);

__attribute__((section(".text.func_00356E98")))
int func_00356E98(SfdWkT *w)
{
    SfdSt1128 *st;

    if (func_00356358(w) == 0) {
        return 1;
    }
    st = &w->tbl->st;
    if (st->f20 == 1) {
        return 1;
    }
    if (st->fC < 3) {
        return 0;
    }
    return 1;
}

