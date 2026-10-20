/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: cCoreSave_ckFightingRingClear, split from src/cod/batch28_nm.c by the NM closer. */
#include "godhand/cCoreSave.h"

__attribute__((section(".text.cCoreSave_ckFightingRingClear")))
int cCoreSave_ckFightingRingClear(cCoreSave *self, unsigned int bit)
{
    cCoreSaveData *data;
    unsigned int w;

    data = self->data;
    if (data == 0)
        return 0;
    w = bit >> 5;
    bit &= 0x1F;
    if (w >= 4)
        return 0;
    return (data->fightingRingClear[w] & (1 << bit)) != 0;
}

