/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct {
    char pad0[0x5C];
    int busy;   /* 0x5C */
} MwsWork;

extern int D_003EC7DC;
extern int D_003EE098;
extern volatile int D_003EE09C;
extern MwsWork *GetD003EC7E0_3452B0(void);
extern int Forward33BF18_348BC8(int *flag);
extern void func_00357240(void);

__attribute__((section(".text.func_00349328")))
void func_00349328(void)
{
    int init = D_003EC7DC;
    MwsWork *w;
    int r;

    D_003EE098++;
    D_003EE09C++;
    if (init == 1) {
        w = GetD003EC7E0_3452B0();
        r = Forward33BF18_348BC8(&w->busy);
        if (r == init) {
            if (D_003EC7DC == r)
                func_00357240();
            w->busy = 0;
        }
    }
}
