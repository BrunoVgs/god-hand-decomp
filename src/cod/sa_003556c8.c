/* cygnus-2.96: func_003556C8, under the lock, picks the best unattached stream entry in state 2 or 4
 * according to func_00355790. */
typedef struct {
    int stat; /* 0x0 */
    char pad4[0x58 - 4];
    int owner; /* 0x58 */
    char pad5C[0xF0 - 0x5C];
} StmEnt;
typedef struct {
    char pad0[0x178];
    int num; /* 0x178 */
    int pad17C;
    StmEnt ent[1]; /* 0x180 */
} StmMgr;
typedef struct {
    char pad0[0x1FC0];
    StmMgr *mgr; /* 0x1FC0 */
} StmSys;
typedef struct {
    int pad[4];
} Lock;
extern void Thunk_func_0033B658(Lock *lk);
extern void Thunk_func_0033B670(Lock *lk);
extern int func_00355790(StmEnt *best, StmEnt *cand);

__attribute__((section(".text.func_003556C8")))
StmEnt *func_003556C8(StmSys *sys)
{
    Lock lk;
    StmEnt *best = 0;
    StmEnt *ent;
    StmMgr *mgr;
    int i, n;

    Thunk_func_0033B658(&lk);
    mgr = sys->mgr;
    n = mgr->num;
    ent = mgr->ent;
    for (i = 0; i < n; i++, ent++) {
        if ((ent->stat == 2 || ent->stat == 4) && ent->owner == -1) {
            if (func_00355790(best, ent) != 0)
                best = ent;
        }
    }
    Thunk_func_0033B670(&lk);
    return best;
}
