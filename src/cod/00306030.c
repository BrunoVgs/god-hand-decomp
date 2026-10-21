/* sn-2.95.3-136: espSys effect resource offset tables (0x306030..). */

#include "godhand/espSys.h"

extern int D_003C2388;
extern void *cIDManager_getTexAddr(void *mgr, int type, int idx);

__attribute__((section(".text.func_00306030")))
void *func_00306030(void *sys, int kind, int idx)
{
    int *ent;
    int *tbl;
    int off;

    if (kind == 3) {
        return func_00305FB0(sys, idx);
    }
    ent = func_003058D8(sys, kind);
    if (ent == 0) {
        return 0;
    }
    tbl = (int *)ent[1];
    if (tbl == 0) {
        return 0;
    }
    if (idx - 1 >= tbl[0]) {
        return 0;
    }
    off = tbl[idx];
    return off == 0 ? 0 : (void *)(off + (int)tbl);
}

__attribute__((section(".text.espSys_getEffT32Addr")))
void *espSys_getEffT32Addr(void *sys, int kind, int idx)
{
    int *ent;
    int *tbl;
    int off;

    if (kind == 0x48) {
        return cIDManager_getTexAddr(D_003C2388, 1, idx);
    }
    ent = func_003058D8(sys, kind);
    if (ent == 0) {
        return 0;
    }
    tbl = (int *)ent[2];
    if (tbl == 0) {
        return 0;
    }
    if (idx >= tbl[0]) {
        return 0;
    }
    off = tbl[idx + 1];
    return off == 0 ? 0 : (void *)(off + (int)tbl);
}
