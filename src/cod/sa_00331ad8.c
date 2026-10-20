/* cygnus-2.96: func_00331AD8, server tick for the stream manager: once its request flag is taken, runs
 * the mode-1 or mode-2 pass (inside the lock pair when that mode asks for it) and the pending flush. */
typedef struct Mgr331AD8 {
    char unk0;
    signed char mode;   /* 0x01 */
} Mgr331AD8;

extern Mgr331AD8 D_003D8410;
extern int D_003D844C;
extern int D_003D8450;
extern int D_003D8454;
extern volatile int D_003D8488;
extern int func_0033BF18(int *flag);
extern void Forward33B568_33B6A0(void);
extern void Forward33B5C8_33B6D0(void);
extern void func_00331718(Mgr331AD8 *m);
extern void func_00331900(Mgr331AD8 *m);
extern void func_00331400(void);

__attribute__((section(".text.func_00331AD8")))
void func_00331AD8(void)
{
    Mgr331AD8 *m = &D_003D8410;

    if (func_0033BF18(&D_003D844C) == 0)
        return;
    if (m->mode == 1) {
        if (D_003D8450 == 1)
            Forward33B568_33B6A0();
        func_00331718(m);
        if (D_003D8450 == 1)
            Forward33B5C8_33B6D0();
    }
    if (m->mode == 2) {
        if (D_003D8454 == 1)
            Forward33B568_33B6A0();
        func_00331900(m);
        if (D_003D8454 == 1)
            Forward33B5C8_33B6D0();
    }
    if (D_003D8488 != 0)
        func_00331400();
    D_003D844C = 0;
}
