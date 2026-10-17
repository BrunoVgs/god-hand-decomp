/* include/godhand/cFlagList.h - a flag table and the index lists that edit it.
 *
 * The owner keeps a table of 0x14-byte flag entries (table, 0x14) and a pool
 * of 16-bit entry indexes (pool, 0x1C). A cFlagListHdr says where its three
 * groups of indexes start in the pool (first) and how many each group holds
 * (num[0..2]); the three groups follow each other. Offsets are exact; unnamed
 * fields stay as unkNN padding. */
#ifndef GODHAND_CFLAGLIST_H
#define GODHAND_CFLAGLIST_H

#define FLAGLIST_GROUP_NUM  3
#define FLAGENT_SIZE        0x14
#define FLAGENT_BIT_ON      0x4     /* bit in cFlagEnt.flags that the clear call drops */

typedef struct cFlagEnt {
    char unk00[0x10];
    unsigned int flags;                 /* 0x10 */
} cFlagEnt;                             /* 0x14 */

typedef struct cFlagListHdr {
    int first;                          /* 0x00 pool index of the first group */
    unsigned char num[FLAGLIST_GROUP_NUM]; /* 0x04 indexes in each group */
} cFlagListHdr;

typedef struct cFlagOwner {
    char unk00[0x14];
    cFlagEnt *table;                    /* 0x14 */
    char unk18[4];
    unsigned short *pool;               /* 0x1C */
} cFlagOwner;

#endif
