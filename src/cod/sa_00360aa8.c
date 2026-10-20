/* cygnus-2.96, -freorder-blocks dropped: func_00360AA8, count down the delayed register write and fire it at zero. */
extern volatile int D_003EEA78;
extern int D_003EEA7C;
extern unsigned int D_003EEA80;
extern volatile unsigned int *D_0045A260[];

__attribute__((section(".text.func_00360AA8")))
void func_00360AA8(void)
{
    D_003EEA78--;
    if (D_003EEA78 == 0 && D_003EEA7C != -1 && (D_003EEA80 & 0xC7) != 0x82)
        *D_0045A260[D_003EEA7C] = D_003EEA80 ^ 0xC00;
    if (D_003EEA78 < 0)
        D_003EEA78 = 0;
}
