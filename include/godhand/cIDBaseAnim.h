/* include/godhand/cIDBaseAnim.h - the animation view of a cIDBase entry's source.
 *
 * Bytes 0x5C..0x6B and the frame counts at the end of parts A, C and D.
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_CIDBASEANIM_H
#define GODHAND_CIDBASEANIM_H

#include "godhand/cIDBase.h"

typedef struct cIDBaseSrcAnim {
    char unk00[4];
    unsigned int flags;         /* 0x04 */
    char unk08[0x54];
    signed char uvStop;         /* 0x5C */
    signed char unk5D;
    signed char stopA;          /* 0x5E */
    signed char stopC;          /* 0x5F */
    char unk60[4];
    signed char stopD;          /* 0x64 */
    char unk65[3];
    unsigned char uvMode;       /* 0x68 0 fwd, 1 ping-pong, 2 rev, 3 rev ping-pong */
    unsigned char uvRate;       /* 0x69 frames per cell */
    unsigned char uvCols;       /* 0x6A */
    unsigned char uvRows;       /* 0x6B */
    char unk6C[0x144];
    short framesA;              /* 0x1B0 */
    char unk1B2[0x62];
    short framesC;              /* 0x214 */
    char unk216[0x62];
    short framesD;              /* 0x278 */
} cIDBaseSrcAnim;

/* Set or clear an entry flag; on is tested as a byte. */
static inline void cIDBaseEnt_setFlag(cIDBaseEnt *ent, int bit, int on)
{
    if ((unsigned char)on)
        ent->flags |= bit;
    else
        ent->flags &= ~bit;
}

#endif
