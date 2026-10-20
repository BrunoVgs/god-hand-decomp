/* include/godhand/mdlPkt.h - model packs and the GIF packets built from them.
 *
 * SN only: `long long` is 128-bit (one quadword) and `unsigned long` 64-bit.
 * Offsets are exact; unnamed fields stay as padding.
 */
#ifndef GODHAND_MDLPKT_H
#define GODHAND_MDLPKT_H

typedef union PktQw {
    long long all;              /* 128-bit in SN */
    struct {
        unsigned long lo;
        unsigned int w8;
        unsigned int wC;
    } s;
} PktQw;

typedef struct MdlPack {
    char pad00[0x20];
    int ofs[1];                 /* 0x20 record offsets from the pack start */
} MdlPack;

typedef struct MdlRec {
    int ofsVtx;                 /* 0x00 */
    int unk04;
    int ofsNrm;                 /* 0x08 */
    int ofsUv;                  /* 0x0C */
    int unk10;
    unsigned short nVtx;        /* 0x14 */
} MdlRec;

typedef struct PackRef {
    MdlPack *base;
    MdlRec *rec;
} PackRef;

typedef struct MdlObj {
    char pad000[0x380];
    int flags;                  /* 0x380 */
    char pad384[4];
    MdlPack *pack;              /* 0x388 */
} MdlObj;

typedef struct GifTagEnt {
    unsigned int w0;
    unsigned int w1;
} GifTagEnt;

typedef struct Pkt0B0 {
    unsigned long q[22];        /* 0xB0, double-buffered */
} Pkt0B0;

extern GifTagEnt D_004A5D80[];

/* A 64-bit packet tag built from a two-word table entry: w0 is the upper word (low 28 bits),
 * w1 the lower word with 0x30000000 set. */
#define TAG64(e) ((unsigned int)((e).w1 | 0x30000000) | ((unsigned long)((e).w0 & 0x0FFFFFFF) << 32))

#endif
