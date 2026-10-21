/* include/godhand/espSys.h - effect system resource tables and memory pool (0x305858..0x307140).
 *
 * func_003058D8 finds the resource entry for an effect kind. entry[1] points
 * at a 1-based offset table, entry[2] at the 0-based T32 table; both start
 * with a count and hold offsets from the table start (0 = no resource).
 * The pool keeps a free list of MemNode blocks with its head node at
 * self + 0x4200; adjacent blocks are merged on free.
 */
#ifndef GODHAND_ESPSYS_H
#define GODHAND_ESPSYS_H

typedef struct espMemNode {
    struct espMemNode *prev;    /* 0x00 */
    struct espMemNode *next;    /* 0x04 */
    char unk08[4];
    char *base;                 /* 0x0C */
    unsigned short size;        /* 0x10 in 16-byte units */
} espMemNode;

#define ESP_MEM_HEAD_OFS 0x4200

extern int *func_003058D8(void *sys, int kind);
extern void *func_00305FB0(void *sys, int idx);
extern void func_00306FC0(char *self, espMemNode *node);

#endif
