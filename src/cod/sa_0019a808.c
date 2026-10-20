/* sn-2.95.3-136: enemy setup with a damage-take volume, then the enemy work defaults (0x19DD30);
 * volume build as SpawnDamageTakeVolumeE. func_001C28A0 takes only self (it clobbers a1/a2 at once). */
#include "godhand/emDamageVol.h"


__attribute__((section(".text.func_0019A808")))
int func_0019A808(EmDmgVol *em)
{
    Vec4f v[4];             /* size twice, offset, rotation */
    Vec4f *ofs;
    Vec4f *rot;
    Vec4f *size;
    void *slot;
    float one, c0, c1;

    func_001B6FB8(em);
    one = 1.0f;
    c0 = 2.4f;
    c1 = 2.0f;
    size = &v[1];
    ofs = &v[2];
    v[0].x = c0;
    v[0].y = one;
    v[0].z = c1;
    v[1].x = c0;
    v[1].z = c1;
    v[0].w = one;
    v[1].y = one;
    size->w = one;
    v[2].x = 0.0f;
    v[2].y = 0.0f;
    v[2].z = 0.0f;
    ofs->w = one;
    slot = cDamageManage_CreateDamageTake(D_00574380, em, 2);
    em->dmgTake = slot;
    if (slot != 0) {
        rot = &v[3];
        v[3].x = 0.0f;
        v[3].y = 0.0f;
        v[3].z = 0.0f;
        rot->w = one;
        func_001FD9D8(slot, (char *)em + 0x80, ofs, rot, size);
    }
    em->base.hpMax = 1;
    em->base.hp = 1;
    em->sub = em->subBuf;
    em->subKind = 5;
    em->unk5EC = 7;
    em->unk5E8 = 0;
    em->unk5E4 = 0;
    em->unk5F0 = 0;
    em->unk5F6 = 0;
    em->target = -1;
    func_001C28A0(em);
    return 1;
}
