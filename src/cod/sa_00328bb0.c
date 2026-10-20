/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
#define ENTRY_NUM     40
#define ENTRY_SIZE    0x60
#define ENTRY_ACTIVE  1

extern volatile int D_003D04C4;
extern char D_003D04D0[];
extern int Obj3290_Tramp_0033BF18_9058(volatile int *flag);
extern void func_003288E0(void *entry);

__attribute__((section(".text.func_00328BB0")))
void func_00328BB0(void)
{
    int active;
    char *e;
    int n;

    if (Obj3290_Tramp_0033BF18_9058(&D_003D04C4) != 0) {
        active = ENTRY_ACTIVE;
        e = D_003D04D0;
        n = ENTRY_NUM - 1;
        do {
            if (*e == active) {
                func_003288E0(e);
            }
            n--;
            e += ENTRY_SIZE;
        } while (n >= 0);
        D_003D04C4 = 0;
    }
}

