/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmHitVolume.h"
extern char D_00574380[];
extern void func_001B6FB8(void *self);
extern void *cDamageManage_CreateDamageTake(void *mgr, void *owner, int kind);
extern void func_001FD9D8(void *slot, void *mtx, float *m, float *nv, float *t);


/* Init: registers the object's damage-take volume (size 4 x 1 x 2) and sets its hit state fields; returns 1. */
__attribute__((section(".text.func_0019BCA0")))
int func_0019BCA0(cOmHitVolume *p)
{
    float f[16];
    float *m;
    float *nv;
    float *t;
    void *slot;
    float one, ca, cb, cc;

    func_001B6FB8(p);
    one = 1.0f;
    ca = 4.0f;
    cb = one;
    cc = 2.0f;
    t = &f[4];
    m = &f[8];
    f[0] = ca;
    f[4] = ca;
    f[1] = cb;
    f[2] = cc;
    f[6] = cc;
    f[3] = one;
    f[5] = cb;
    t[3] = one;
    f[8] = 0.0f;
    f[9] = 0.0f;
    f[10] = 0.0f;
    m[3] = one;
    slot = cDamageManage_CreateDamageTake(D_00574380, p, 2);
    p->damageTake = slot;
    if (slot != 0) {
        nv = &f[12];
        f[12] = 0.0f;
        f[13] = 0.0f;
        f[14] = 0.0f;
        nv[3] = one;
        func_001FD9D8(slot, p->base.mtx, m, nv, t);
    }
    p->base.hpMax = 1;
    p->base.hp = 1;
    p->table = p->tableData;
    p->count = 0xC;
    p->unk5EC = 7;
    p->unk5E8 = 0;
    p->unk5F4 = -1;
    p->unk5E4 = 0;
    p->unk5F0 = 0;
    p->unk5F6 = 0;
    func_001C28A0(p);
    return 1;
}
