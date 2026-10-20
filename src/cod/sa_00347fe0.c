/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
/* cygnus-2.96 (drop-reorder): func_00347FE0, split from src/cod/sa_nm_00347e58.c by the NM closer. */

#include "godhand/mwsfHn.h"

extern char D_004591A0[];
extern char D_004591D0[];
extern char D_00459210[];

void func_00347FE0(MwsfHn *mw);
int func_00348098(MwsfHn *mw);

__attribute__((section(".text.func_00347FE0")))
void func_00347FE0(MwsfHn *mw)
{
    int time, tunit;
    unsigned int mode;

    func_00346968(mw, &time, &tunit);
    mode = mw->mode;
    mw->busy = 1;
    switch (mode) {
    case 1:
        func_00347968(mw, mw->f1A4);
        break;
    case 2:
        func_00347BC0(mw, mw->f2EC, mw->f2F0);
        break;
    case 3:
        func_00347D08(mw, mw->f1A4, mw->f2F4, mw->f2F8);
        break;
    }
    mw->busy = 0;
    mw->count++;
}

