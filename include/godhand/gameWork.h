/* include/godhand/gameWork.h - the game work block at D_007474A0 and the
 * render packet chain built from it.
 *
 * Most older TUs still see D_007474A0 as a plain char array; this typed view
 * is for code that names its fields. Field names are ours; offsets are exact.
 */
#ifndef GODHAND_GAMEWORK_H
#define GODHAND_GAMEWORK_H

#define GAMEWORK_PLAYER_READY   0x00010000  /* flags: the player object exists */
#define GAMEWORK_SKIP_PKT_1_3   0x02000000  /* flags: packets 1-3 left out of the chain */
#define GAMEWORK_IN_INTERRUPT   0x20000000  /* flags: flush with iFlushCache */
#define GAMEWORK_STAGE_NOPLAYER 0x20        /* stage: no player object */

typedef struct GameWork {
    char pad000[0x210];
    int frame;                  /* 0x210 bit 0 picks the packet buffer */
    char pad214[0x578 - 0x214];
    int mode;                   /* 0x578 */
    char pad57C[0x584 - 0x57C];
    int flags;                  /* 0x584 GAMEWORK_* */
    char pad588[0x598 - 0x588];
    int flags598;               /* 0x598 */
    char pad59C[0x5B0 - 0x59C];
    unsigned short stage;       /* 0x5B0 */
    char pad5B2[0x5C0 - 0x5B2];
    float startPos[3];          /* 0x5C0 player start point */
    char pad5CC[4];
    float startAngle;           /* 0x5D0 */
    char pad5D4[0x5E4 - 0x5D4];
    int flags5E4;               /* 0x5E4 */
    char pad5E8[0x5F4 - 0x5E8];
    void *playerObj;            /* 0x5F4 */
} GameWork;

extern GameWork D_007474A0;
extern int D_00747A24;          /* D_007474A0.flags under its own symbol */

/* One 0x80-byte DMA packet; the chain has 11, each double-buffered. */
typedef struct Pkt31A3 {
    char data[0x80];
} Pkt31A3;

typedef struct PktSet31A3 {
    Pkt31A3 pkt[11][2];
} PktSet31A3;

typedef struct cTaskWorkRef {
    int unk0;
    int task;                   /* 0x4 */
} cTaskWorkRef;

extern cTaskWorkRef D_00752C00;

extern void func_0014FE78(char *pkt);
extern void SetPackedFields10And18_14FF60(int pkt, int *next);
extern int func_003950F8(int mode, int timeout);   /* GS path sync */
extern void FlushCache(int op);
extern void iFlushCache(int op);
extern void cTaskWork_sleep(int task, int frames);

#endif
