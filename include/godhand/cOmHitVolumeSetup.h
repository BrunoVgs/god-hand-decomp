/* include/godhand/cOmHitVolumeSetup.h - the calls the cOmHitVolume setup routines share
 * (sn code at 0x188DE0..0x1A3B80).
 */
#ifndef GODHAND_COMHITVOLUMESETUP_H
#define GODHAND_COMHITVOLUMESETUP_H

#include "godhand/cOmHitVolume.h"

/* The setup steps the family shares. */
extern int func_001B6FB8(cOmHitVolume *self);    /* cOmBase constructor step */
extern int func_001C28A0(cOmHitVolume *self);    /* enemy work defaults */
extern void *cDamageManage_CreateDamageTake(void *mgr, void *owner, int kind);
extern int func_001FD9D8(void *unit, void *mtx, cVec *ofs, cVec *rot, cVec *size);
extern char D_00574380[];                               /* the damage manager */

static __inline__ void cOmHitVolume_setVec(cVec *v, float x, float y, float z, float w)
{
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

#endif /* GODHAND_COMHITVOLUMESETUP_H */
