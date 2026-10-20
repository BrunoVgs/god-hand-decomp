/* cygnus-2.96 (no -freorder-blocks): Sofdec per-channel helpers (0x34F7A0..). */
#include "godhand/mwsfd.h"

__attribute__((section(".text.func_0034F7A0")))
int func_0034F7A0(SfdHn *hn)
{
    SfdChSet *set = &hn->ch;
    int ret = 0;

    if (set->chA != SFD_CH_NONE) {
        ret = func_0034CA30(hn, set->chA);
    }
    if (set->chB != SFD_CH_NONE) {
        ret |= func_0034CA30(hn, set->chB);
    }
    if (set->chC != SFD_CH_NONE) {
        ret |= func_0034CA30(hn, set->chC);
    }
    return ret;
}

__attribute__((section(".text.func_0034F830")))
void func_0034F830(SfdHn *hn, int arg)
{
    SfdChSet *set = &hn->ch;

    if (set->chA != SFD_CH_NONE) {
        func_0034CA00(hn, set->chA, arg);
    }
    if (set->chB != SFD_CH_NONE) {
        func_0034CA00(hn, set->chB, arg);
    }
    if (set->chC != SFD_CH_NONE) {
        func_0034CA00(hn, set->chC, arg);
    }
}
