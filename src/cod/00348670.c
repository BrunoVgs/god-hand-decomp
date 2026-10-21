/* cygnus-2.96: open slot id and fill its 0x20-byte record, or report one of three errors and return 0. */
typedef struct MwsfdSlotOwner {
    char pad0[0x3C];
    int unk3C;
} MwsfdSlotOwner;

typedef struct MwsfdSlot {
    int flag;     /* 0x00 */
    int id;       /* 0x04 */
    int opened;   /* 0x08 */
    int a2;       /* 0x0C */
    int a3;       /* 0x10 */
    int span;     /* 0x14 */
    int a4;       /* 0x18 */
    int made;     /* 0x1C */
} MwsfdSlot;

extern char D_00459240[];
extern char D_00459270[];
extern char D_00459298[];
extern int func_00348938(int id);
extern void func_00348258(int id);
extern int func_00348338(int id, int *p0, int *p1, int *p2);
extern int func_003395A0(int a, int b, int c);
extern int func_003483A0(int id, int a2, int p0);
extern void func_0034E090(int ctx, int a, int span, int z0, int z1);
extern void MWSFSVM_Error(char *msg);

__attribute__((section(".text.func_00348670")))
int func_00348670(MwsfdSlotOwner *o, int id, int a2, int a3, int a4)
{
    int p0;
    int p1;
    int p2;
    MwsfdSlot *s;
    int opened;
    int span;
    int made;
    int ctx;

    opened = func_00348938(id);
    if (opened == 0)
        return 0;
    func_00348258(id);
    ctx = o->unk3C;
    s = (MwsfdSlot *)((char *)o + (id << 5) + 0x284);
    s->opened = opened;
    s->id = id;
    s->a2 = a2;
    s->a3 = a3;
    s->a4 = a4;
    if (a3 < func_00348338(id, &p0, &p1, &p2)) {
        MWSFSVM_Error(D_00459240);
        return 0;
    }
    span = func_003395A0(a2 + p0, p1, p2);
    if (span == 0) {
        MWSFSVM_Error(D_00459270);
        return 0;
    }
    s->span = span;
    made = func_003483A0(id, a2, p0);
    if (made == 0) {
        MWSFSVM_Error(D_00459298);
        return 0;
    }
    s->made = made;
    s->flag = 1;
    func_0034E090(ctx, a4 + 0xC0, span, 0, 0);
    return made;
}
