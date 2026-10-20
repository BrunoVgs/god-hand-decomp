/* Batch 34: unique SN ~100 (scratch-only). */
#include "include_asm.h"
extern void CustomIDWork_SetDisp(void *p, int f);
extern void *SearchData(void *a0, void *a1, int a2);
extern void func_001B6FB8(void *self);
extern void espSys_effDataRegist(void *a0, int a1, void *a2);
extern int SetEffect(int a0, int a1, void *a2, int a3, int t0, unsigned t1);
extern void sceSifInitRpc(int mode);
extern void func_00377BC8(void);
extern void func_00375860(void);
extern void func_003758E8(int which);
extern char D_007419A0[];
extern char D_0044FEA0[];
extern char D_0076A880[];
extern char D_0076A9C0[];
extern char D_0076B1C0[];

__attribute__((section(".text.func_00305358")))
void func_00305358(int *out, void *key)
{
    void *table = D_0044FEA0;
    void *k = key;
    int *o = out;

    *(o + 1) = (int)SearchData(k, table, 0);
    *o = (int)SearchData(k, table, 1);
}

INCLUDE_ASM("nonmatching", func_00375318);
