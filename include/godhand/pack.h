/* include/godhand/pack.h - packed resource archives.
 *
 * A pack starts with a small header, then a table of entry offsets measured
 * from the pack start. Keyed packs (func_00151630 == 3) follow the offset
 * table with a table of 64-bit keys, aligned up to 8 bytes.
 */
#ifndef GODHAND_PACK_H
#define GODHAND_PACK_H

typedef struct Pack {
    int unk00;
    int count;                  /* 0x04 */
    int unk08[2];
    int ofs[1];                 /* 0x10 entry offsets from the pack start */
} Pack;

extern int func_00151630(Pack *pack);                       /* pack type, 3 = keyed */
extern int func_00152340(Pack *pack, long key);             /* index of key, or -1 */
extern char *cIDBase_getSlotPtr(void *unused, Pack *pack, unsigned char idx);

#endif
