/* cygnus-2.96: Sofdec SUD stream-type table lookups (0x346DD0..). */

#include "godhand/mwsfHn.h"

__attribute__((section(".text.func_00346DD0")))
int func_00346DD0(SudStmTbl *tbl, int no)
{
    int i = no % 8;

    if (tbl->ent[i].state != 1) {
        return 0;
    }
    return tbl->ent[i].type;
}

__attribute__((section(".text.func_00346E20")))
int func_00346E20(SudStmTbl *tbl, int no)
{
    int i = no % 8;

    if (tbl->ent[i].state != 1) {
        return 0x11;
    }
    return tbl->ent[i].ccs;
}
