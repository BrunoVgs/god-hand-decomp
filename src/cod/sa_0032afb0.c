/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
extern void Forward33B658_33E678(void);
extern void Forward33B670_33E690(void);
extern void func_003276A8(void);
extern void func_0032CFC8(char *p);
extern void Obj3260_Tramp_00338638_D390(void);
extern char D_003C7420[];
extern volatile int D_003D140C;
extern int D_003D1414;

__attribute__((section(".text.func_0032AFB0")))
void func_0032AFB0(void)
{
    int i;
    char *p;

    Forward33B658_33E678();
    if (D_003D140C != 0) {
        Forward33B670_33E690();
        return;
    }
    D_003D140C = 1;
    Forward33B670_33E690();
    Forward33B658_33E678();
    func_003276A8();
    D_003D140C = 2;
    for (i = 0; i < 16; i++) {
        p = D_003C7420 + i * 0xC8;
        if (*p == 1) {
            func_0032CFC8(p);
        }
    }
    D_003D140C = 3;
    Obj3260_Tramp_00338638_D390();
    if (D_003D1414 < 0x33) {
        Obj3260_Tramp_00338638_D390();
    }
    D_003D140C = 0;
    Forward33B670_33E690();
}
