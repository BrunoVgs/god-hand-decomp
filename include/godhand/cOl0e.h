/* include/godhand/cOl0e.h - the cOl0e scripted collision object.
 *
 * A cOl0e can be switched into a fake state: its damage volumes go inactive,
 * the hit entry at 0xDA8 loses its active bit and the object drops to mode 1,
 * so it still draws but takes no hits. Switching back reverses all of it.
 *
 * The base part (flags at 0x5B0 and 0x5B8, the four state bytes at 0x2F4,
 * the animation rate at 0x24C) is cOmBase. Only the fields the methods drawn
 * so far touch are named. Offsets are exact; a span nobody has named stays
 * unkNNN padding.
 */
#ifndef GODHAND_COL0E_H
#define GODHAND_COL0E_H

#include "godhand/cOmBase.h"
#include "godhand/cDamageUnit.h"

#define COL0E_FLAG2_FAKE    0x100       /* flags2: the object is in the fake state */
#define COL0E_HIT_ACTIVE    0x1         /* cOl0eHit.flags: the hit entry is live */

/* The hit entry the object registered: its flags are at 0x8. */
typedef struct cOl0eHit {
    char unk00[8];
    int flags;                          /* 0x08 COL0E_HIT_ACTIVE */
} cOl0eHit;

typedef struct cOl0e {
    cOmBase base;
    char unk5E0[0x20];
    cDamageUnit *damage;                /* 0x600 */
    char unk604[0xD9B - 0x604];
    unsigned char fake;                 /* 0xD9B 1 while in the fake state */
    char unkD9C[0xC];
    cOl0eHit *hit;                      /* 0xDA8 */
} cOl0e;

typedef char cOl0e_chk_fake[((int)&((cOl0e *)0)->fake == 0xD9B) ? 1 : -1];
typedef char cOl0e_chk_hit[((int)&((cOl0e *)0)->hit == 0xDA8) ? 1 : -1];
typedef char cOl0e_chk_damage[((int)&((cOl0e *)0)->damage == 0x600) ? 1 : -1];

#endif
