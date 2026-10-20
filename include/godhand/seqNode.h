/* include/godhand/seqNode.h - sequence nodes, links and stop commands (sn code at 0x37C330..).
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_SEQNODE_H
#define GODHAND_SEQNODE_H

typedef struct SeqRange {
    char unk00[0x18];
    short min;                  /* 0x18 */
    short max;                  /* 0x1A */
} SeqRange;

typedef struct SeqTimer {
    short f30;                  /* 0x30 */
    short f32;                  /* 0x32 */
    short unk34;
    short f36;                  /* 0x36 */
} SeqTimer;

typedef struct SeqNode {
    unsigned short flags;       /* 0x00 */
    short id;                   /* 0x02 */
    char unk04;
    unsigned char kind;         /* 0x05 */
    unsigned short sub;         /* 0x06 */
    struct SeqNode *parent;     /* 0x08 */
    int busy;                   /* 0x0C */
    int owner;                  /* 0x10 */
    char unk14[0x30 - 0x14];
    SeqTimer timer;             /* 0x30 */
    char unk38[0x50 - 0x38];
} SeqNode;

typedef struct SeqLink {
    unsigned short flags;       /* 0x00 */
    char unk02[3];
    unsigned char kind;         /* 0x05 */
    char unk06[2];
    SeqNode *node;              /* 0x08 */
    char unk0C[4];
    int owner;                  /* 0x10 */
    char unk14[0x20 - 0x14];
} SeqLink;

typedef struct SeqCmd {
    char unk00[4];
    int owner;                  /* 0x04 */
    char unk08[5];
    unsigned char mask;         /* 0x0D */
    short all;                  /* 0x0E */
    short arg;                  /* 0x10 */
} SeqCmd;

extern char D_0076A600[];       /* node data, 0x84 stride */
extern SeqLink D_0076C8C0[];    /* 51 entries */
extern SeqNode D_0076CF20[];    /* 51 entries */

extern void func_0037D148(SeqNode *n);
extern void func_0037D3B0(SeqNode *n);
extern void func_0037D820(SeqNode *n);
extern void func_0037D8B8(SeqNode *n, short arg);
extern void func_00378020(SeqTimer *t);

#endif /* GODHAND_SEQNODE_H */
