/* cygnus-2.96, -freorder-blocks dropped, as=sn: func_00359F78, run func_0035A000(hn, a0, a1) on every handle that is not busy;
 * twin of sa_0035a620.c. */
extern void *D_003EE2C4[8];
extern int Obj34D8_SetGlobalEE0B8_IfField48(void *hn);
extern void func_0035A000(void *hn, int a0, int a1);

__attribute__((section(".text.func_00359F78")))
void func_00359F78(int a0, int a1)
{
    int i;
    void *hn;

    for (i = 0; i < 8; i++) {
        hn = D_003EE2C4[i];
        if (Obj34D8_SetGlobalEE0B8_IfField48(hn) == 0)
            func_0035A000(hn, a0, a1);
    }
}
