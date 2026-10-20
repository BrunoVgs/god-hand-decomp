/* sn-2.95.3-136: cIDBase per-entry animation steps (0x2ABCE8..). */
#include "godhand/cIDBaseAnim.h"

__attribute__((section(".text.func_002ABCE8")))
void func_002ABCE8(cIDBaseObj *self, cIDBaseEnt *ent)
{
    cIDBaseSrcAnim *src = (cIDBaseSrcAnim *)ent->src;
    short n = src->framesA;

    ent->jit[2] = 0;
    if (src->stopA == 0)
        cIDBaseEnt_setFlag(ent, 0x1000, n < 2);
}

__attribute__((section(".text.func_002ABD30")))
void func_002ABD30(cIDBaseObj *self, cIDBaseEnt *ent)
{
    cIDBaseSrcAnim *src = (cIDBaseSrcAnim *)ent->src;
    short n = src->framesC;

    ent->jit[3] = 0;
    if (src->stopC == 0)
        cIDBaseEnt_setFlag(ent, 0x800, n < 2);
}

__attribute__((section(".text.func_002ABD78")))
void func_002ABD78(cIDBaseObj *self, cIDBaseEnt *ent)
{
    cIDBaseSrcAnim *src = (cIDBaseSrcAnim *)ent->src;
    short n = src->framesD;

    ent->jit[4] = 0;
    if (src->stopD == 0)
        cIDBaseEnt_setFlag(ent, 0x400, n < 2);
}
