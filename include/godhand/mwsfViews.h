#ifndef GODHAND_MWSFVIEWS_H
#define GODHAND_MWSFVIEWS_H

/* Partial views of the MWSF ring, SFD clear table, ADX player, SFD work and MWSF handle used by
 * the cygnus singletons. Only the fields these functions touch are named. */

typedef struct MwRingEnt {
    int stat;                   /* 0x00 */
    char unk04[0x0C - 0x04];
    int val;                    /* 0x0C */
    char unk10[0x14 - 0x10];
} MwRingEnt;

typedef struct MwRing {
    char unk00[0xB8];
    int pos;                    /* 0xB8 */
    char unkBC[0xC0 - 0xBC];
    MwRingEnt ent[8];           /* 0xC0 */
} MwRing;

typedef struct SfdPair {
    int a;
    int b;
} SfdPair;

typedef struct SfdClr {
    int f00[7];                 /* 0x00 */
    SfdPair ent[16];            /* 0x1C */
} SfdClr;

typedef struct AdxPlay {
    char unk00[0x9C];
    short mode;                 /* 0x9C */
} AdxPlay;

typedef struct SfdSt1128 {
    char unk00[0x0C];
    int fC;                     /* 0x0C */
    char unk10[0x20 - 0x10];
    int f20;                    /* 0x20 */
} SfdSt1128;

typedef struct SfdTbl {
    char unk0000[0x1128];
    SfdSt1128 st;               /* 0x1128 */
} SfdTbl;

typedef struct SfdWkT {
    char unk0000[0x1FC0];
    SfdTbl *tbl;                /* 0x1FC0 */
} SfdWkT;

typedef struct MwsfHn48 {
    char unk00[0x48];
    void *f48;                  /* 0x48 */
} MwsfHn48;

#endif /* GODHAND_MWSFVIEWS_H */
