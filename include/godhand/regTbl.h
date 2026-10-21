/* include/godhand/regTbl.h - the name/id registry tables and the paired-key table
 * (sn code at 0x393FD8..0x394D00).
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_REGTBL_H
#define GODHAND_REGTBL_H

/* One registry entry, looked up by name (compared with func_003A5678) and id. */
typedef struct RegEnt {
    int name;                   /* 0x00 */
    int value;                  /* 0x04 */
    unsigned short id;          /* 0x08 */
    unsigned char kind;         /* 0x0A 1..4 */
    unsigned char active;       /* 0x0B */
} RegEnt;

/* One registered table; the tables form a list from D_003F852C. */
typedef struct RegTbl {
    char unk00[4];
    int handleA;                /* 0x04 */
    int handleB;                /* 0x08 */
    RegEnt *ents;               /* 0x0C */
    int count;                  /* 0x10 */
    char unk14[0x30 - 0x14];
    struct RegTbl *next;        /* 0x30 */
} RegTbl;

extern RegTbl *D_003F852C;

/* The paired-key table at D_003F5520: each entry keeps a ^ key ^ 0x31415926 as a check. */
typedef struct PairTblEnt {
    int a;                      /* 0x00 */
    int key;                    /* 0x04 */
    int check;                  /* 0x08 */
} PairTblEnt;

typedef struct PairTbl {
    unsigned int count;         /* 0x00 */
    int check;                  /* 0x04 count ^ 0x31415926 */
    PairTblEnt ent[0x400];      /* 0x08 */
} PairTbl;

extern PairTbl D_003F5520;

#endif /* GODHAND_REGTBL_H */
