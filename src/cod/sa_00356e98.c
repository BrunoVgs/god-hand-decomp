/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
/* cygnus-2.96 (drop-reorder): func_00356E98, split from src/cod/sa_nm_00345250.c by the NM closer. */

#include "godhand/mwsfViews.h"

extern void func_0033E3B8(AdxPlay *p);
extern void func_0033E220(AdxPlay *p);
extern void func_0033E0A8(AdxPlay *p);
extern int func_00356358(SfdWkT *w);
extern int GetField0OrZero_346828(MwsfHn48 *mw);
extern void MWSFSVM_Error(const char *msg);
extern void func_00335C68(void *p, int v);
extern char D_00458F48[];

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

