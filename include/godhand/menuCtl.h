/* include/godhand/menuCtl.h - menu list control and file-select menus (sn code at 0x37FD28..0x385xxx).
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_MENUCTL_H
#define GODHAND_MENUCTL_H

typedef struct MenuPad {
    char unk00[0x38];
    unsigned int trg;           /* 0x38 */
} MenuPad;

typedef struct MenuInfo {
    int f00;                    /* 0x00 */
    int f04;                    /* 0x04 */
    int f08;                    /* 0x08 */
    int f0C;                    /* 0x0C */
    char unk10[0x30 - 0x10];
    int handle;                 /* 0x30 */
} MenuInfo;

typedef struct MenuList {
    unsigned char unk00;
    unsigned char result;       /* 0x01 */
    char unk02[2];
    short unk04;                /* 0x04 */
    char unk06[2];
    short unk08;                /* 0x08 */
    short unk0A;                /* 0x0A */
    char unk0C[0x10 - 0x0C];
    unsigned int count;         /* 0x10 */
    MenuInfo work;              /* 0x14 */
    char unk48[0x4C - 0x48];
    MenuInfo info;              /* 0x4C */
    char unk80[0x84 - 0x80];
    int f84;                    /* 0x84 */
} MenuList;

typedef struct MenuCtl {
    unsigned char unk00;
    unsigned char unk01;
    unsigned char state;        /* 0x02 */
    unsigned char unk03[4];
    unsigned char cursor;       /* 0x07 */
    char unk08[0x470 - 0x08];
    MenuList list;              /* 0x470 */
} MenuCtl;

typedef struct SlotInfoA {
    char unk00[0x14];
    int info;                   /* 0x14 */
    char unk18[0x20 - 0x18];
    int handle;                 /* 0x20 */
    int buf;                    /* 0x24 freed once the handle stops */
} SlotInfoA;

typedef struct SlotInfoB {
    char unk00[0x10];
    int info;                   /* 0x10 */
    int size;                   /* 0x14 */
    float time;                 /* 0x18 */
    int stamp;                  /* 0x1C */
    char unk20[0x30 - 0x20];
    int handle;                 /* 0x30 */
    int buf;                    /* 0x34 freed once the handle stops */
} SlotInfoB;

typedef struct SlotView {
    unsigned char unk00[3];
    unsigned char flags;        /* 0x03 */
    char unk04[0x30 - 0x04];
    int stat;                   /* 0x30 */
    SlotInfoB b;                /* 0x34 */
    char unk6C[0xA4 - 0x34 - sizeof(SlotInfoB)];
    SlotInfoA a;                /* 0xA4 */
} SlotView;

typedef struct FileList {
    char unk00[8];
    int count;                  /* 0x08 */
} FileList;

typedef struct FileSelWork {
    unsigned char unk00;
    unsigned char err;          /* 0x01 */
    unsigned char unk02[2];
    unsigned char busy;         /* 0x04 */
    char unk05[0xF4 - 0x05];
    int req;                    /* 0xF4 */
    void *buf;                  /* 0xF8 */
    FileList *list;             /* 0xFC */
} FileSelWork;

typedef struct FileSel {
    unsigned char unk00[2];
    unsigned char state;        /* 0x02 */
    unsigned char unk03[3];
    unsigned char cursor;       /* 0x06 */
    char unk07[0x370 - 0x07];
    FileSelWork work;           /* 0x370 */
} FileSel;

extern int GuardedCall_00329FD0_329F98(int handle);
extern int func_00380AE8(MenuCtl *ctl, MenuInfo *info, MenuList *list);
extern void func_00380EB0(MenuCtl *ctl, MenuInfo *info, MenuList *list);
extern int func_0037FD28(FileSel *sel, FileSelWork *work);
extern int func_00323918(int a0, int idx);

/* One row of the option menu pages (D_003F21E8, D_003F2368, D_003F24D0). */
typedef struct MenuRowEnt {
    short unk0;
    short unk2;
    short unk4;
    short y;                            /* 0x06 */
    char unk8;
    signed char handler;                /* 0x09 index into D_003F2628 */
    char unkA[0xA];
} MenuRowEnt;

extern MenuRowEnt D_003F21E8[];
extern MenuRowEnt D_003F2368[];
extern MenuRowEnt D_003F24D0[];

/* The track set a sound option drives: its count and the player handle (0x24 bytes). */
typedef struct SndTrkSet {
    char unk00[8];
    int count;                          /* 0x08 */
    char unk0C[0x20 - 0x0C];
    void *ply;                          /* 0x20 player handle */
} SndTrkSet;

/* The voice reference of a sound option (the handle at 0x30). */
typedef struct SndVoiceRef {
    char unk00[0x30];
    void *voice;                        /* 0x30 voice handle */
} SndVoiceRef;

#endif /* GODHAND_MENUCTL_H */
