/* sn-2.95.3-136: func_003825A8, applies the per-track left/right volume tables to every track of a player. */
#include "godhand/menuCtl.h"
typedef struct {
    char pad0[0x18];
    short lvol[5]; /* 0x18 */
    short rvol[7]; /* 0x22 */
    SndTrkSet trk; /* 0x30 */
} VolTbl;
extern void *func_0032DCD0(void *ply, int n);
extern void func_0032A6D0(void *adxt, int ch, int vol);

__attribute__((section(".text.func_003825A8")))
void func_003825A8(void *unused, VolTbl *v)
{
    SndTrkSet *trk = &v->trk;
    void *adxt;
    int i;

    for (i = 0; i < trk->count; i++) {
        adxt = func_0032DCD0(trk->ply, i);
        func_0032A6D0(adxt, 0, v->lvol[i + 1]);
        func_0032A6D0(adxt, 1, v->rvol[i + 1]);
    }
}
