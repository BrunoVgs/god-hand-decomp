/* Batch 43: unique SN ~124 (scratch-only). */

extern int cModel_setTextureExchange(void *self, void *tex, void *tbl, int n);
extern int func_00387430(int a0);
extern void *func_00377998(void);

__attribute__((section(".text.func_003870E0")))
int func_003870E0(short id)
{
    short s0 = id;
    int v0;
    char *a3;

    v0 = func_00387430(s0);
    if (v0 & 8)
        return -1;
    a3 = func_00377998();
    if (a3 == 0)
        return -1;
    *(short *)(a3 + 0xC) = s0;
    *(short *)(a3 + 0) = 1;
    a3[8] = 0x10;
    a3[9] = 2;
    *(short *)(a3 + 0xA) = 2;
    *(int *)(a3 + 4) = 0;
    return 0;
}
