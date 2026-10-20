#ifndef GODHAND_SNDSYS76A790_H
#define GODHAND_SNDSYS76A790_H

/* The 0xC4-byte block at D_0076A790: a version name copied in at reset
 * (func_00377BC8) and the transfer timing peaks kept by func_00375500. */
typedef struct SndSys76A790 {
    char name[14];              /* 0x00 */
    char unk0E[0xE];
    int unk1C;                  /* 0x1C */
    short unk20;                /* 0x20 */
    char unk22[0x62];
    int unk84;                  /* 0x84 */
    char unk88[0xC];
    unsigned int hblanks;       /* 0x94 */
    unsigned int hblanksMax;    /* 0x98 */
    unsigned int usec;          /* 0x9C */
    unsigned int usecMax;       /* 0xA0 */
    char unkA4[4];
    unsigned int unkA8;         /* 0xA8 */
    char unkAC[0x18];
} SndSys76A790;                 /* 0xC4 */

typedef char SndSys76A790_size_check[(sizeof(SndSys76A790) == 0xC4) ? 1 : -1];

extern SndSys76A790 D_0076A790;

#endif
