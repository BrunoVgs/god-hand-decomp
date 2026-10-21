/* include/godhand/EntryPool.h - a fixed pool of 24-byte entries.
 *
 * The pool size is a global set at run time; an entry with `used` == 0 is
 * free.
 */
#ifndef GODHAND_ENTRYPOOL_H
#define GODHAND_ENTRYPOOL_H

typedef struct PoolEntry {
    signed char used;                   /* 0x00 0 = free */
    signed char unk01[23];
} PoolEntry;                            /* 0x18 */

#endif
