/* sn-2.95.3-136: func_003825A8, applies the per-track left/right volume tables to every track of a player. */
typedef struct {
    char pad0[8];
    int ntrk; /* 0x08 */
    char padC[0x20 - 0xC];
    void *ply; /* 0x20 */
} TrkSet;
typedef struct {
    char pad0[0x18];
    short lvol[5]; /* 0x18 */
    short rvol[7]; /* 0x22 */
    TrkSet trk; /* 0x30 */
} VolTbl;
extern void *func_0032DCD0(void *ply, int n);
extern void func_0032A6D0(void *adxt, int ch, int vol);

__attribute__((section(".text.func_003825A8")))
void func_003825A8(void *unused, VolTbl *v)
{
    TrkSet *trk = &v->trk;
    void *adxt;
    int i;

    for (i = 0; i < trk->ntrk; i++) {
        adxt = func_0032DCD0(trk->ply, i);
        func_0032A6D0(adxt, 0, v->lvol[i + 1]);
        func_0032A6D0(adxt, 1, v->rvol[i + 1]);
    }
}
