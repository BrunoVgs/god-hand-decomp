/* cygnus-2.96 (drop-reorder): stream/SFD/sound singletons (batch 40). */

typedef struct StmHn {
    char unk00;
    char stat;                  /* 0x01 */
    char unk02[0x38 - 0x02];
    int vol;                    /* 0x38 */
    char unk3C[0x56 - 0x3C];
    char mode;                  /* 0x56 */
} StmHn;

typedef struct SfdTbl1FC0 {
    char unk000[0x178];
    int n;                      /* 0x178 */
    char unk17C[4];
    char ent[1][0xF0];          /* 0x180 */
} SfdTbl1FC0;

typedef struct SfdWk16B0 {
    char unk0000[0x16B0];
    char ent[1][0x88];          /* 0x16B0 */
} SfdWk16B0;

typedef struct AdxHn {
    char unk00[0x0E];
    char stat;                  /* 0x0E */
    char unk0F[0xE8 - 0x0F];
    int fE8;                    /* 0xE8 */
} AdxHn;

typedef struct SndObj {
    char unk000[0x38];
    int state;                  /* 0x38 */
    char unk03C[0x48 - 0x3C];
    int f48;                    /* 0x48 */
    char unk04C[0x118 - 0x4C];
    int f118;                   /* 0x118 */
    char unk11C[0x134 - 0x11C];
    int f134;                   /* 0x134 */
} SndObj;

extern int D_003E0708;
extern int D_003E0710;
extern int func_00327B58(int a0, int a1, int a2, void *a3);
extern int func_00327C30(int a0, int a1, int a2, void *a3);
extern void func_0033F130(const char *msg);
extern char D_004568D0[];

__attribute__((section(".text.func_00338788")))
void func_00338788(StmHn *h, int vol)
{
    if (D_003E0710 == 1 && D_003E0708 <= 0) {
        return;
    }
    if (vol > 0) {
        vol = 0;
    }
    if (vol < -999) {
        vol = -999;
    }
    h->vol = vol;
}

__attribute__((section(".text.func_00327D48")))
void func_00327D48(void *p, int n)
{
    long r;

    if (n < 0x100) {
        r = func_00327B58(0, 0, 0, p);
    } else {
        r = func_00327C30(0, 0, 0, p);
    }
}

__attribute__((section(".text.func_00337B80")))
void func_00337B80(StmHn *h, unsigned int mode)
{
    if (D_003E0710 == 1 && D_003E0708 <= 0) {
        return;
    }
    if (mode < 2 && h->mode != mode) {
        h->stat = h->mode;
        h->mode = mode;
    }
}

__attribute__((section(".text.func_00355490")))
void *func_00355490(SfdWk16B0 *w, void *key)
{
    SfdTbl1FC0 *t = *(SfdTbl1FC0 **)((char *)w + 0x1FC0);
    char *e;
    int i;

    for (i = 0, e = t->ent[0]; i < t->n; i++, e += 0xF0) {
        if (e == key) {
            return w->ent[i];
        }
    }
    return 0;
}

__attribute__((section(".text.func_0033CE98")))
int func_0033CE98(AdxHn *h)
{
    if (h->stat == 1 && h->fE8 != 0) {
        return 2;
    }
    if (h == 0) {
        func_0033F130(D_004568D0);
        return -1;
    }
    return h->stat;
}

__attribute__((section(".text.func_0036E2B8")))
void func_0036E2B8(SndObj *o)
{
    if (o->f48 == 1 || o->f118 == 1 || o->f118 == 2) {
        o->state = 1;
    } else if (o->f134 == 1) {
        o->state = 3;
    } else {
        o->state = 2;
    }
}
