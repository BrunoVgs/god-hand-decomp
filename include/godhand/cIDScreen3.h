/* include/godhand/cIDScreen3.h - a screen made of a main cIDBase display and
 * three more cIDBase displays at 0x4B0, 0x500 and 0x550 (0x50 bytes apart).
 * Setup restarts every display's animation, and keeps pointers to the first
 * display entry of each part. Offsets are exact; fields nobody has named stay
 * as unkNN padding. */
#ifndef GODHAND_CIDSCREEN3_H
#define GODHAND_CIDSCREEN3_H

#include "godhand/cIDBase.h"

#define IDSCREEN3_PART_SIZE   0x50
#define IDSCREEN3_ENT_NUM     2
#define IDSCREEN3_COLOR_GREY  0x80808080
#define IDSCREEN3_PULSE       20.0f

/* A cIDBase display padded to the 0x50-byte spacing of the three parts. */
typedef struct cIDScreen3Part {
    cIDBaseObj base;
    char unk48[IDSCREEN3_PART_SIZE - 0x48];
} cIDScreen3Part;

typedef struct cIDScreen3 {
    cIDBaseObj base;                    /* 0x000 */
    char unk48[0x90 - 0x48];
    int f90;                            /* 0x090 */
    char unk94[4];
    void *player;                       /* 0x098 */
    char unk9C[0x4A0 - 0x9C];
    cIDBaseEnt *ent[IDSCREEN3_ENT_NUM]; /* 0x4A0 entries 0 and 1 of the main display */
    char unk4A8[8];
    cIDScreen3Part partC;               /* 0x4B0 */
    cIDScreen3Part partA;               /* 0x500 */
    cIDScreen3Part partB;               /* 0x550 */
    cIDBaseEnt *entC;                   /* 0x5A0 first entry of partC */
    cIDBaseEnt *entA;                   /* 0x5A4 first entry of partA */
    cIDBaseEnt *entB;                   /* 0x5A8 first entry of partB */
    char unk5AC[0x5D0 - 0x5AC];
    float pulse;                        /* 0x5D0 */
    char unk5D4[4];
    unsigned int color;                 /* 0x5D8 */
    unsigned char flag5DC;              /* 0x5DC */
    unsigned char flag5DD;              /* 0x5DD */
} cIDScreen3;

typedef char cIDScreen3_chk_ent[((int)&((cIDScreen3 *)0)->ent == 0x4A0) ? 1 : -1];
typedef char cIDScreen3_chk_partB[((int)&((cIDScreen3 *)0)->partB == 0x550) ? 1 : -1];
typedef char cIDScreen3_chk_color[((int)&((cIDScreen3 *)0)->color == 0x5D8) ? 1 : -1];

#endif
