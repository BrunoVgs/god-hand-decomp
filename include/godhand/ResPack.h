/* include/godhand/ResPack.h - a counted resource pack.
 *
 * Word 0 is the entry count n. Words 1..n are entry offsets, relative to the
 * pack. Words n+1..2n are the 4-byte entry names, in the same order.
 */
#ifndef GODHAND_RESPACK_H
#define GODHAND_RESPACK_H

typedef struct ResPack {
    unsigned int count;                 /* 0x0 n */
    unsigned int offs[1];               /* 0x4 n offsets, then n names */
} ResPack;

#endif
