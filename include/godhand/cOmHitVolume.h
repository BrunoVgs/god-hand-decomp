/* include/godhand/cOmHitVolume.h - a cOmBase object that owns a damage-take volume.
 *
 * The setup routines of this family (SpawnDamageTakeVolume* and their siblings) run the cOmBase
 * constructor step, build two or three float vectors on the stack, ask the damage manager for a
 * damage-take unit, register the box with it, then fill the tail of the record that follows the
 * cOmBase part: five cleared or constant words, an entry table at 0x620 and its count.
 *
 * Offsets are exact. A field nobody has named yet stays as unkNNN padding.
 */
#ifndef GODHAND_COMHITVOLUME_H
#define GODHAND_COMHITVOLUME_H

#include "godhand/cOmBase.h"

typedef struct cOmHitVolume {
    cOmBase base;                       /* 0x000 */
    char unk5E0[4];
    int unk5E4;                         /* 0x5E4 cleared at setup */
    int unk5E8;                         /* 0x5E8 cleared at setup */
    int unk5EC;                         /* 0x5EC 0, 7 or 0x11 at setup, per kind */
    int unk5F0;                         /* 0x5F0 cleared at setup */
    short unk5F4;                       /* 0x5F4 -1 at setup */
    short unk5F6;                       /* 0x5F6 0 or 0x2E at setup, per kind */
    char unk5F8[8];
    void *damageTake;                   /* 0x600 the unit the damage manager returned, 0 when none */
    void *damageGive;                   /* 0x604 damage-give unit, on the kinds that have one */
    void *table;                        /* 0x608 points at tableData */
    unsigned char count;                /* 0x60C number of table entries in use */
    char unk60D[0x13];
    char tableData[1];                  /* 0x620 */
} cOmHitVolume;

#define COMHITVOLUME_OFFSET(f) ((int)&((cOmHitVolume *)0)->f)
typedef char cOmHitVolume_chk_hp[COMHITVOLUME_OFFSET(base.hp) == 0x54A ? 1 : -1];
typedef char cOmHitVolume_chk_table[COMHITVOLUME_OFFSET(table) == 0x608 ? 1 : -1];
typedef char cOmHitVolume_chk_data[COMHITVOLUME_OFFSET(tableData) == 0x620 ? 1 : -1];

#endif
