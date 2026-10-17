/* include/godhand/cFontTex.h - the font texture resource and its slot table.
 *
 * A font texture resource (cFontTexRes) starts with a flag word whose bit 31
 * is set once its internal offsets have been turned into addresses. After
 * the header come two lists of 16-byte entries, each entry holding an
 * offset at +4 that setTextureAddr turns into an address. cFont keeps one
 * 16-byte slot per loaded texture: the resource, its info record and four
 * numbers copied from the info. Offsets are exact; unnamed fields stay as
 * unkNN padding. */
#ifndef GODHAND_CFONTTEX_H
#define GODHAND_CFONTTEX_H

#define CFONTTEX_FIXED       0x80000000   /* flags: offsets already turned into addresses */
#define CFONTTEX_ENT_SIZE    0x10

typedef struct cFontTexEnt {
    int unk00;
    int addr;                           /* 0x04 offset from the resource start, then an address */
    char unk08[8];
} cFontTexEnt;                          /* 0x10 */

typedef struct cFontTexRes {
    unsigned int flags;                 /* 0x00 CFONTTEX_FIXED when done */
    unsigned short w4;                  /* 0x04 */
    unsigned short w6;                  /* 0x06 */
    int offA;                           /* 0x08 offset of the first entry list */
    int offB;                           /* 0x0C offset of the second entry list */
    unsigned short numA;                /* 0x10 entries in the first list */
    unsigned short numB;                /* 0x12 entries in the second list */
} cFontTexRes;

typedef struct cFontTexInfo {
    unsigned short h0;                  /* 0x00 */
    unsigned short h2;                  /* 0x02 */
    unsigned short h4;                  /* 0x04 */
    unsigned char b6;                   /* 0x06 */
    unsigned char b7;                   /* 0x07 */
} cFontTexInfo;

typedef struct cFontTexSlot {
    cFontTexRes *res;                   /* 0x00 */
    cFontTexInfo *info;                 /* 0x04 */
    unsigned short h8;                  /* 0x08 copy of info->h2 */
    unsigned short hA;                  /* 0x0A copy of info->h4 */
    unsigned short hC;                  /* 0x0C copy of info->b6 */
    unsigned short hE;                  /* 0x0E copy of info->b7 */
} cFontTexSlot;                         /* 0x10 */

#endif
