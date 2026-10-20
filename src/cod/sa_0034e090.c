/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct {
    char pad0[0x40];
    void *sj[0x44]; /* 0x40, ids 0xBC..0xFF */
    int a; /* 0x150 */
    int b; /* 0x154 */
} StmTbl;
typedef struct {
    char pad0[0x1F7C];
    StmTbl *tbl; /* 0x1F7C */
} StmHn;
extern int Obj34D8_SetGlobalEE0B8_IfField48(void *obj);
extern int func_0034DD70(int a0, unsigned int a1);

__attribute__((section(".text.func_0034E090")))
int func_0034E090(StmHn *hn, int id, void *sj, int a, int b)
{
    StmTbl *tbl;
    int r;

    r = Obj34D8_SetGlobalEE0B8_IfField48(hn);
    if (r != 0) {
        return func_0034DD70(0, 0xFF000171);
    }
    if ((unsigned int)(id - 0xBC) < 0x44) {
        tbl = hn->tbl;
        tbl->b = b;
        tbl->sj[id - 0xBC] = sj;
        tbl->a = a;
    }
    return r;
}
