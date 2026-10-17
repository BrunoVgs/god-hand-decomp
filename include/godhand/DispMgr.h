/* include/godhand/DispMgr.h - DispMgr, the registry of display sub-records.
 *
 * A DispMgr holds eleven sub-records at fixed offsets, then a table of
 * registered objects at 0x22F0 (12 bytes per slot). func_00140BF0 registers
 * a sub-record in the first free slot and DispMgr_reset (src/cod/00140c88.c)
 * walks the table to call every object's reset method.
 *
 * Field names are ours, taken from the functions that read and write them.
 * Offsets are exact. A field we can't name yet stays as unkNN padding.
 */
#ifndef GODHAND_DISPMGR_H
#define GODHAND_DISPMGR_H

#define DISPMGR_SLOT_NUM  0x11          /* FindFreeSlotIndex_140C58 stops at 0x11 */
#define DISPMGR_SLOT_OFS  0x22F0        /* byte offset of slot[0] */

typedef struct DispMgrSlot {
    int kind;                           /* 0x0 what the sub-record is, 0 = free is judged on obj */
    void *obj;                          /* 0x4 the registered sub-record, 0 when the slot is free */
    int unk8;
} DispMgrSlot;                          /* 0xC */

typedef struct DispMgr {
    char unk0000[DISPMGR_SLOT_OFS];
    DispMgrSlot slot[DISPMGR_SLOT_NUM]; /* 0x22F0 */
} DispMgr;

#endif
