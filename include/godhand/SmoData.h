/* include/godhand/SmoData.h - the "SMO" object-parameter data block.
 *
 * A block starts with the magic SMO_MAGIC, an entry count and a format
 * version. Version 0 and 1 headers are 3 words long; later versions add a
 * fourth word. SmoReader holds the block and the address of its body.
 */
#ifndef GODHAND_SMODATA_H
#define GODHAND_SMODATA_H

#define SMO_MAGIC         0x534D4F  /* "OMS\0" read as a little-endian word */
#define SMO_VERSION_LONG  2         /* first version with a 4-word header */

typedef struct SmoHeader {
    unsigned int magic;                 /* 0x0 SMO_MAGIC */
    unsigned int count;                 /* 0x4 entries, 0 = empty block */
    unsigned int version;               /* 0x8 */
    unsigned int body[1];               /* 0xC body, or the 4th header word from SMO_VERSION_LONG on */
} SmoHeader;

typedef struct SmoReader {
    SmoHeader *hdr;                     /* 0x0 0 when no valid block is bound */
    unsigned int *body;                 /* 0x4 first word after the header */
} SmoReader;

#endif
