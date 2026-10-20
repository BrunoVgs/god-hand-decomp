/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
/* cygnus-2.96 (drop-reorder): func_00345250, split from src/cod/sa_nm_00345250.c by the NM closer. */

#include "godhand/mwsfViews.h"

extern void func_0033E3B8(AdxPlay *p);
extern void func_0033E220(AdxPlay *p);
extern void func_0033E0A8(AdxPlay *p);
extern int func_00356358(SfdWkT *w);
extern int GetField0OrZero_346828(MwsfHn48 *mw);
extern void MWSFSVM_Error(const char *msg);
extern void func_00335C68(void *p, int v);
extern char D_00458F48[];

__attribute__((section(".text.func_00345250")))
int func_00345250(MwRing *r)
{
    int i = r->pos % 8;

    if (r->ent[i].stat != 1)
        return 0;
    return r->ent[i].val;
}

