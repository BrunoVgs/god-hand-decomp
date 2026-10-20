/* sn-2.95.3-136: func_002F2898, enemy action setup from its parameter block: copies counts, range and offsets, resolves the start position. */
typedef struct {
    float x, y, z;
} Vec2F2898;

typedef struct {
    float x, y, z, w;
} Vec4F2898;

typedef struct {
    char pad0[0x13C];
    float range;          /* 0x13C */
    char pad140[0x8];
    Vec2F2898 ofs;        /* 0x148 */
    char pad154[0x18];
    int kind;             /* 0x16C */
    int arg;              /* 0x170 */
    char pad174[0x18];
    unsigned char count;  /* 0x18C */
    signed char track;    /* 0x18D */
} Prm2F2898;

typedef struct {
    char pad0[0x103];
    signed char node;     /* 0x103 */
    char pad104[0xC];
    Prm2F2898 *prm;       /* 0x110 */
    char pad114[0x10C];
    char work[0x90];      /* 0x220 */
    int kind;             /* 0x2B0 */
    int arg;              /* 0x2B4 */
    int count;            /* 0x2B8 */
    char pad2BC[0x4];
    Vec2F2898 pos;        /* 0x2C0 */
    char pad2CC[0x4];
    unsigned char track;  /* 0x2D0 */
    char pad2D1[0x3];
    int handle;           /* 0x2D4 */
    float range;          /* 0x2D8 */
    char pad2DC[0x4];
    Vec4F2898 ofs;        /* 0x2E0 */
} Act2F2898;

extern char D_0044EED0[];
extern char D_0044EEE8[];
extern void func_002D9F68(Act2F2898 *a, char *msg, int v);
extern void func_002B6310(Vec2F2898 *out, Act2F2898 *a);
extern void StoreVecFromFieldB0_2B6160(Vec2F2898 *out, Act2F2898 *a);
extern int func_0031D098(void *work);

static inline void Set2F2898(Vec4F2898 *d, float x, float y, float z)
{
    d->x = x;
    d->y = y;
    d->z = z;
    d->w = 1.0f;
}

static inline void Copy2F2898(Vec2F2898 *d, Vec2F2898 *s)
{
    if (d != s) {
        d->x = s->x;
        d->y = s->y;
        d->z = s->z;
    }
}

__attribute__((section(".text.func_002F2898")))
int func_002F2898(Act2F2898 *a)
{
    Prm2F2898 *p = a->prm;
    Vec2F2898 v;
    int kind;

    a->range = p->range;
    a->kind = p->kind;
    a->arg = p->arg;
    if (a->kind >= 3) {
        func_002D9F68(a, D_0044EED0, a->kind);
        return 0;
    }
    if (a->kind == 0)
        a->count = p->count + 1;
    else
        a->count = p->count;

    a->track = a->prm->track != 0;
    Set2F2898(&a->ofs, a->prm->ofs.x, a->prm->ofs.y, a->prm->ofs.z);

    if (a->node == -1)
        func_002B6310(&v, a);
    else
        StoreVecFromFieldB0_2B6160(&v, a);
    Copy2F2898(&a->pos, &v);

    if (a->track)
        a->handle = func_0031D098(a->work);

    kind = a->kind;
    if (kind == 1 && a->count == 0) {
        func_002D9F68(a, D_0044EEE8, 0);
        a->count = kind;
    }
    return 1;
}
