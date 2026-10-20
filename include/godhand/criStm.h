/* include/godhand/criStm.h - CRI stream handle pool (cygnus code at 0x336E88..).
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_CRISTM_H
#define GODHAND_CRISTM_H

typedef struct StmObjVtbl {
    void *unk00[3];
    void (*destroy)(void *obj);                     /* 0x0C */
    void *unk10[4];
    void (*setBuf)(void *obj, int idx, void *desc); /* 0x20 */
} StmObjVtbl;

typedef struct StmObj {
    StmObjVtbl *vt;
} StmObj;

typedef struct StmEnt {
    char used;                  /* 0x00 */
    void *f4;                   /* 0x04 */
    StmObj *obj;                /* 0x08 */
    void *sjx;                  /* 0x0C */
    char *buf;                  /* 0x10 */
    int bufSize;                /* 0x14 */
} StmEnt;

extern int D_003E0708;          /* pool entry count */
extern int D_003E070C;          /* heap size */
extern int D_003E0710;          /* config flag */
extern void *D_003E0714;        /* IOP heap block */
extern char *D_003E0718;        /* aligned heap base */
extern char D_003E071C;         /* heap owned */
extern StmEnt D_003E0768[];

/* printf-style logger. */
extern void func_003260C8(const char *fmt, ...);
/* memset; callers depend on the void * return. */
extern void *func_003A52F0(void *dst, int c, int n);

#endif /* GODHAND_CRISTM_H */
