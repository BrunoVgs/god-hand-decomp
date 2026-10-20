/* Batch 34: unique SN ~100 (scratch-only). */
#include "include_asm.h"
extern void *SearchData(void *a0, void *a1, int a2);
extern char D_0044FEA0[];

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
