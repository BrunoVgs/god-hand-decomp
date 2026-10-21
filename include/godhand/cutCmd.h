/* include/godhand/cutCmd.h - cutscene frame-range and SE voice commands (sn code at 0x2B2D88..).
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_CUTCMD_H
#define GODHAND_CUTCMD_H

#define CUT_CURRENT            0xFF

typedef union CutNo {
    unsigned short w;
    unsigned char b;
} CutNo;

typedef struct CutFrmRec {
    char unk00[2];
    CutNo first;                        /* 0x2 */
    unsigned short firstFrame;          /* 0x4 */
    CutNo last;                         /* 0x6 */
    unsigned short lastFrame;           /* 0x8 */
} CutFrmRec;

typedef struct CutFrmCmd {
    char unk00[0x44];
    unsigned char cutFirst;             /* 0x44 */
    char unk45[3];
    int frameFirst;                     /* 0x48 */
    unsigned char cutLast;              /* 0x4C */
    char unk4D[3];
    int frameLast;                      /* 0x50 */
    char unk54[0x8C - 0x54];
    CutFrmRec *rec;                     /* 0x8C */
} CutFrmCmd;

typedef struct SeOwner {
    char unk000[0x304];
    void *seName;                       /* 0x304 */
} SeOwner;

typedef struct SeCmd {
    char unk00[0x18];
    SeOwner *owner;                     /* 0x18 */
    void *se;                           /* 0x1C */
    int voice;                          /* 0x20 */
    char unk24[0x30 - 0x24];
    unsigned char count;                /* 0x30 */
    char unk31[0x7C - 0x31];
    void *cur;                          /* 0x7C */
    char unk80[0x84 - 0x80];
    int prev;                           /* 0x84 */
    unsigned short wait;                /* 0x88 */
    char unk8A[0x8C - 0x8A];
    void *rec;                          /* 0x8C */
    int next;                           /* 0x90 */
} SeCmd;

extern float cEvent_getCutFrame(void *ev);

#endif /* GODHAND_CUTCMD_H */
