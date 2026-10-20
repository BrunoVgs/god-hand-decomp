extern void Forward33B658_3389F8(void);
extern void func_00332398(void *);
extern void Forward33B670_338A10(void);
extern signed char D_003D84C0[];

__attribute__((section(".text.func_00332778")))
void func_00332778(void)
{
    signed char *entry;
    int remaining;
    Forward33B658_3389F8();
    entry = D_003D84C0;
    for (remaining = 15; remaining >= 0; remaining--) {
        if (*entry == 1)
            func_00332398(entry);
        entry += 0x44;
    }
    Forward33B670_338A10();
}
