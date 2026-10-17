/* include/godhand/cNowLoading.h - the now-loading screen record.
 *
 * It lives inside the game object (offset 0x3A0) and starts with a cIDBase
 * display object. After the display object come two pulse slots and a few
 * fields that the setup code fills from the display entries. Offsets are
 * exact; fields nobody has named yet stay as unkNN padding. */
#ifndef GODHAND_CNOWLOADING_H
#define GODHAND_CNOWLOADING_H

#include "godhand/cIDBase.h"

#define NOWLOADING_SLOT_NUM    2        /* entries 0 and 1 each get a slot */
#define NOWLOADING_ENT_NUM     4        /* display entries 0..3 */
#define NOWLOADING_SLOT_ONE    1.0f
#define NOWLOADING_SLOT_TWO    2.0f
#define NOWLOADING_BAR_LEN     256.0f   /* value of barLen at setup */

/* One slot: constants plus two values copied from a display entry. */
typedef struct cNowLoadingSlot {
    float two;                  /* 0x00 starts at 2.0 */
    float one;                  /* 0x04 starts at 1.0 */
    float copyA;                /* 0x08 copy of the entry's f70[1] */
    float copyB;                /* 0x0C copy of the entry's f70[3] */
} cNowLoadingSlot;              /* 0x10 */

typedef struct cNowLoading {
    cIDBaseObj base;            /* 0x00 */
    char unk48[0x90 - 0x48]; /* cIDBaseObj is 0x48 bytes */
    cNowLoadingSlot slot[NOWLOADING_SLOT_NUM]; /* 0x90 */
    int unkB0;                  /* 0xB0 cleared at setup */
    float barX;                 /* 0xB4 posX of display entry 2 */
    float barLen;               /* 0xB8 */
    unsigned char unkBC;        /* 0xBC cleared at setup */
} cNowLoading;

typedef char cNowLoading_chk_slot[((int)&((cNowLoading *)0)->slot == 0x90) ? 1 : -1];
typedef char cNowLoading_chk_barX[((int)&((cNowLoading *)0)->barX == 0xB4) ? 1 : -1];

#endif
