/* cygnus-2.96: func_00359F78, run func_0035A000(hn, ...) on every handle that is not busy. */
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
