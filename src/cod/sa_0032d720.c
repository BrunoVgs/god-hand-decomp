/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct SjIf32D720 {
    char pad0[0xC];
    void (*destroy)(void *);
} SjIf32D720;

typedef struct Sj32D720 {
    SjIf32D720 *vt;
} Sj32D720;

typedef struct Adxt32D720 {
    char used;
    char pad1[2];
    signed char maxnch;
    void *sjf;
    int stm;
    int rna;
    char pad10[0x7C];
    Sj32D720 *sjo;
    char pad90[4];
    Sj32D720 *sji[1];
} Adxt32D720;

extern char D_004529F8[];
extern void Obj33F8_Tramp_0033F130_FCB0(char *msg);
extern void func_0032DBA0(void);
extern void func_003283E8(int stm, int a, int b);
extern void func_00327D90(int stm);
extern void func_0032EE88(Adxt32D720 *adxt);
extern void Obj33F8_Tramp_0033B658_FC70(void);
extern void Obj33F8_Tramp_0033B670_FC88(void);
extern void func_0032F428(void *sjf);
extern void *func_003A52F0(void *p, int c, int n);

__attribute__((section(".text.func_0032D720")))
void func_0032D720(Adxt32D720 *adxt)
{
    int stm;
    int i;
    Sj32D720 *sj;
    void *sjf;

    if (adxt == 0) {
        Obj33F8_Tramp_0033F130_FCB0(D_004529F8);
        return;
    }
    func_0032DBA0();
    stm = adxt->stm;
    if (stm != 0) {
        adxt->stm = 0;
        func_003283E8(stm, 0, 0);
        func_00327D90(stm);
    }
    if (adxt->rna != 0)
        func_0032EE88(adxt);
    Obj33F8_Tramp_0033B658_FC70();
    for (i = 0; i < adxt->maxnch; i++) {
        if (adxt->sji[i] != 0) {
            Sj32D720 *t = adxt->sji[i];
            adxt->sji[i] = 0;
            t->vt->destroy(t);
        }
    }
    sj = adxt->sjo;
    if (sj != 0) {
        adxt->sjo = 0;
        sj->vt->destroy(sj);
    }
    sjf = adxt->sjf;
    if (sjf != 0) {
        adxt->sjf = 0;
        func_0032F428(sjf);
    }
    func_003A52F0(adxt, 0, 0x278);
    adxt->used = 0;
    Obj33F8_Tramp_0033B670_FC88();
}
