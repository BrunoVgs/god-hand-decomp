/* include/godhand/cOl2b.h - the cOl2b scripted collision object.
 *
 * Only the fields the methods drawn so far touch are named. The base part
 * (flags at 0x250 and 0x5B8, the part table at 0x278, the four state bytes
 * at 0x2F4) is shared with the other cOl objects. The object moves three
 * parts between fixed positions (setInitFix, setOpenFix, setCloseFix write
 * state 0, 1 and 2). Offsets are exact; a span nobody has named stays
 * unkNNN padding.
 */
#ifndef GODHAND_COL2B_H
#define GODHAND_COL2B_H

#define COL2B_FLAG250_OPEN   0x10000    /* flags250: the door is open */
#define COL2B_FLAG5B8_FIXED  0x8        /* flags5B8: position is fixed */
#define COL2B_STATE_INIT     0          /* state at 0xA24 */
#define COL2B_STATE_OPEN     1
#define COL2B_STATE_OPENING  2
#define COL2B_STATE_CLOSE    2
#define COL2B_PART_NUM       3          /* parts the fix routines place */

/* One movable part: its position vector at 0x100. */
typedef struct cOl2bPart {
    char unk000[0x100];
    float pos[3];                       /* 0x100 */
} cOl2bPart;

typedef struct cOl2b {
    char unk000[0x250];
    unsigned int flags250;              /* 0x250 */
    char unk254[0x24];
    cOl2bPart **part;                   /* 0x278 part pointer table */
    char unk27C[0x38];
    unsigned char partNum;              /* 0x2B4 entries in the part table */
    char unk2B5[0x3F];
    unsigned char mode;                 /* 0x2F4 the four state bytes the move code clears together */
    unsigned char phase;                /* 0x2F5 */
    unsigned char step;                 /* 0x2F6 */
    unsigned char stepArg;              /* 0x2F7 */
    char unk2F8[0x2C0];
    unsigned int flags5B8;              /* 0x5B8 */
    char unk5BC[0x468];
    int state;                          /* 0xA24 */
    unsigned char stateA28;             /* 0xA28 */
    unsigned char stateA29;             /* 0xA29 */
} cOl2b;

typedef char cOl2b_chk_part[((int)&((cOl2b *)0)->part == 0x278) ? 1 : -1];
typedef char cOl2b_chk_mode[((int)&((cOl2b *)0)->mode == 0x2F4) ? 1 : -1];
typedef char cOl2b_chk_flags5B8[((int)&((cOl2b *)0)->flags5B8 == 0x5B8) ? 1 : -1];
typedef char cOl2b_chk_state[((int)&((cOl2b *)0)->state == 0xA24) ? 1 : -1];

#endif
