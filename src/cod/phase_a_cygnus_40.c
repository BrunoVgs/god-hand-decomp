/* cygnus-2.96 matched 40-byte Phase A functions.
 * The entry pointer is volatile so the counter's address load stays
 * after the store, and the null branch keeps its nop delay. */
extern int D_003EE800;
extern int D_003F1EC8;

__attribute__((section(".text.func_0035FFB0")))
void func_0035FFB0(volatile int *entry)
{
    if (entry == 0)
        return;
    *entry = 0;
    D_003EE800 -= 1;
}

__attribute__((section(".text.func_0036CB98")))
void func_0036CB98(volatile int *entry)
{
    if (entry == 0)
        return;
    *entry = 0;
    D_003F1EC8 -= 1;
}
