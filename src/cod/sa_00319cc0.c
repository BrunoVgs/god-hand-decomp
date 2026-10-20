#include "godhand/gameWork.h"
/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_00319CC0, split from src/cod/batch46_nm.c by the NM closer. */
extern int GetField_2B1_14B638(void *self);
extern void *cModel_getMeshPtr(void *self, int i);
extern void Forward155AE8_148F00(void *a0, int a1);
extern void func_00155BE8(void *arg0, int arg1, int arg2);

__attribute__((section(".text.func_00319CC0")))
void func_00319CC0(void *self, int value)
{
    int i;
    int n = GetField_2B1_14B638(self);

    for (i = 0; i < n; i++)
        Forward155AE8_148F00(cModel_getMeshPtr(self, i), value | 0x80000000);
    func_00155BE8(self, value, D_007474A0.frame & 1);
}
