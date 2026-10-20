/* cygnus-2.96: MWSFD handle setters. */

#include "godhand/mwsfViews.h"

extern int GetField0OrZero_346828(MwsfHn48 *mw);
extern void MWSFSVM_Error(const char *msg);
extern void func_00335C68(void *p, int v);
extern char D_00458F48[];

__attribute__((section(".text.func_00347908")))
void func_00347908(MwsfHn48 *mw, int v)
{
    if (GetField0OrZero_346828(mw) != 1) {
        MWSFSVM_Error(D_00458F48);
        return;
    }
    func_00335C68(mw->f48, v);
}
