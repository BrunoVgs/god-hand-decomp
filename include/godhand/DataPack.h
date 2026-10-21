/* include/godhand/DataPack.h - an offset-table data pack and the object that holds it.
 *
 * A DataPack starts with a table of section offsets at 0x20. Entry i, added
 * to the pack's own address, gives section i. A section carries its item
 * count at 0x14. The owner keeps its pack pointer at 0x388. Names are ours;
 * unnamed fields stay as unkNN padding.
 */
#ifndef GODHAND_DATAPACK_H
#define GODHAND_DATAPACK_H

#define DATAPACK_ITEMS_PER_BLOCK  24     /* items that share one buffer block */
#define DATAPACK_BUF_HEADER       0x10   /* bytes in front of the first block */

typedef struct DataPackSection {
    char unk00[0x14];
    unsigned short count;               /* 0x14 items in this section */
} DataPackSection;

typedef struct DataPack {
    char unk00[0x20];
    int offs[1];                        /* 0x20 section offsets, relative to the pack */
} DataPack;

typedef struct DataPackOwner {
    char unk000[0x388];
    DataPack *pack;                     /* 0x388 */
} DataPackOwner;

/* A pack and one of its sections, kept together as a local pair. */
typedef struct DataPackRef {
    DataPack *pack;
    DataPackSection *sect;
} DataPackRef;

#endif
