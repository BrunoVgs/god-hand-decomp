/* include/godhand/mwPly.h - the movie player handle (cygnus code at 0x32DA78..0x32E3A0).
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_MWPLY_H
#define GODHAND_MWPLY_H

#include "godhand/criSj.h"

typedef struct MwPly {
    char unk000;
    unsigned char stat;         /* 0x001 1..3 while it plays */
    char unk002[2];
    int adx;                    /* 0x004 the ADX decoder handle */
    void *sfd;                  /* 0x008 */
    char unk00C[0x8C - 0x0C];
    int sjDefault;              /* 0x08C an SjObj *, held as an int */
    int sj;                     /* 0x090 the input SjObj *, held as an int */
    char unk094[0x1AC - 0x94];
    int unk1AC;                 /* 0x1AC */
    char unk1B0[2];
    unsigned char unk1B2;       /* 0x1B2 */
    char unk1B3[0x1D0 - 0x1B3];
    int unk1D0;                 /* 0x1D0 */
    int unk1D4;                 /* 0x1D4 */
    int unk1D8;                 /* 0x1D8 */
    int unk1DC;                 /* 0x1DC */
    int ownSj;                  /* 0x1E0 the player created sj itself */
} MwPly;

#endif /* GODHAND_MWPLY_H */
