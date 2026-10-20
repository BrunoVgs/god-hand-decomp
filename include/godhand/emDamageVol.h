/* include/godhand/emDamageVol.h - the enemies built by the damage-volume setup family
 * (sn code at 0x188DE0..0x1A3B80): a cOmBase with a damage-take volume and a sub-record.
 *
 * Field names are ours where cOmBase.h has none; offsets are exact.
 */
#ifndef GODHAND_EMDAMAGEVOL_H
#define GODHAND_EMDAMAGEVOL_H

#include "godhand/cOmBase.h"
#include "godhand/vec.h"

typedef struct EmDmgVol {
    cOmBase base;               /* 0x000 hpMax 0x548, hp 0x54A */
    char unk5E0[4];
    int unk5E4;                 /* 0x5E4 */
    int unk5E8;                 /* 0x5E8 */
    int unk5EC;                 /* 0x5EC */
    int unk5F0;                 /* 0x5F0 */
    short target;               /* 0x5F4 -1 = none */
    short unk5F6;               /* 0x5F6 */
    char unk5F8[0x600 - 0x5F8];
    void *dmgTake;              /* 0x600 damage-take volume */
    void *dmgGive;              /* 0x604 damage-give volume */
    char *sub;                  /* 0x608 points at subBuf */
    unsigned char subKind;      /* 0x60C */
    char unk60D[0x620 - 0x60D];
    char subBuf[1];             /* 0x620 */
} EmDmgVol;

/* Takes only the enemy. */
extern int func_001C28A0(EmDmgVol *em);
extern int func_001B6FB8(EmDmgVol *em);
extern void *cDamageManage_CreateDamageTake(void *mgr, void *owner, int kind);
extern int func_001FD9D8(void *slot, void *mtx, Vec4f *ofs, Vec4f *rot, Vec4f *size);
extern char D_00574380[];

static inline void EmDmgVol_setVec4(Vec4f *v, float x, float y, float z, float w)
{
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

#endif /* GODHAND_EMDAMAGEVOL_H */
