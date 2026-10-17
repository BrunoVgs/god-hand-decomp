/* include/godhand/SlotUi.h - SlotUi, the slot machine's on-screen panel.
 *
 * SlotUi is a cIDBase whose display entries are CustomIDWork records
 * (0x7C bytes each): ten at 0x50 (the reel and line marks) and two at 0x580
 * (the bet marks). A second cIDBase sits at 0x530. The panel owns a heap node
 * at 0x678. Slot1 and Slot2 call func_001E73C0 to build it and
 * func_001E7368 to release it.
 *
 * Field names are ours, taken from the functions that read and write them.
 * Offsets are exact. A field we can't name yet stays as unkNNN padding.
 */
#ifndef GODHAND_SLOTUI_H
#define GODHAND_SLOTUI_H

#define SLOTUI_MARK_NUM      10         /* entries at markBase */
#define SLOTUI_BET_NUM       2          /* entries at betBase */
#define SLOTUI_ENTRY_SIZE    0x7C       /* sizeof(CustomIDWork) */

/* The global record at **D_003C2384; only the two words cleared at release are named. */
typedef struct SlotUiHost {
    char unk00[0x88];
    int pickA;                          /* 0x88 */
    int pickB;                          /* 0x8C */
} SlotUiHost;

typedef struct SlotUi {
    char idBase[0x530];                 /* 0x000 the cIDBase part; the mark entries start at 0x50 */
    char idBase2[0x50];                 /* 0x530 second cIDBase */
    char betBase[0xF8];                 /* 0x580 the bet mark entries */
    int *node;                          /* 0x678 heap node, 0 when none; word -8 is its heap */
} SlotUi;

#endif
