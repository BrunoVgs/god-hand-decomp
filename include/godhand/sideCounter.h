/* include/godhand/sideCounter.h - the side counter at D_00754C38 (read by the side check at 0x319848). */
#ifndef GODHAND_SIDECOUNTER_H
#define GODHAND_SIDECOUNTER_H

typedef struct SideCounter {
    char pad0[4];
    unsigned char on;           /* 0x04 */
    unsigned char side;         /* 0x05 */
    char pad6[2];
    int cnt;                    /* 0x08 */
} SideCounter;

extern SideCounter D_00754C38;

#endif /* GODHAND_SIDECOUNTER_H */
