/* cygnus-2.96: func_00329E08, stops a stream player: halts the SJ, releases the reader and clears the state. */
typedef struct RdObj RdObj;
typedef struct {
    void *f0, *f4, *f8;
    void (*destroy)(RdObj *o); /* 0x0C */
} RdVtbl;
struct RdObj { RdVtbl *vt; };

typedef struct {
    char pad0;
    signed char stat;   /* 0x01 */
    signed char kind;   /* 0x02 */
    char pad3;
    void *dec;          /* 0x04 */
    char pad8[4];
    void *sj;           /* 0x0C */
    char pad10[4];
    RdObj *rd;          /* 0x14 */
    char pad18[0x74 - 0x18];
    void *buf;          /* 0x74 */
    char pad78[0xAC - 0x78];
    char eos;           /* 0xAC */
} StmPly;

extern void Forward33B658_33E678(void);
extern void Forward33B670_33E690(void);
extern void Obj3260_Tramp_003382A0_D320(void *sj, int id);
extern void Obj3260_Tramp_00338338_D338(void *sj, int id);
extern void func_00338378(void *sj, int id);
extern void func_00326860(void *dec);
extern void func_0033C228(void *buf);

__attribute__((section(".text.func_00329E08")))
void func_00329E08(StmPly *p)
{
    RdObj *rd;

    Forward33B658_33E678();
    Obj3260_Tramp_003382A0_D320(p->sj, 0);
    Obj3260_Tramp_00338338_D338(p->sj, 0);
    func_00338378(p->sj, 1);
    func_00326860(p->dec);
    if (p->kind == 2) {
        rd = p->rd;
        if (rd != 0) {
            p->rd = 0;
            rd->vt->destroy(rd);
        }
    }
    if (p->buf != 0)
        func_0033C228(p->buf);
    p->rd = 0;
    p->stat = 0;
    p->eos = 0;
    Forward33B670_33E690();
}
