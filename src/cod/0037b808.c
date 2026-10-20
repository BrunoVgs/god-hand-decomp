typedef struct {
    short *val;
    char pad4[5];
    signed char enabled;
    short min;
    unsigned short max;
    short step;
    short step2;
    char pad12[2];
} MenuValEnt;

typedef struct {
    char pad0[0x27];
    signed char row;
    signed char col;
    char sel;
    char pad2A[2];
    int flags;
    char pad30[8];
    int pad;
    char pad3C[0x16C - 0x3C];
    struct { short id; char pad[0x0E]; int handle; char pad2[0x0C]; } slot[1];
} MenuValAct;

extern MenuValEnt D_003F26E8[][6];
extern int func_00374AE0(int id);

__attribute__((section(".text.func_0037B808")))
int func_0037B808(MenuValAct *a)
{
    int row = a->row;
    MenuValEnt *e = &D_003F26E8[row][a->col];
    short v, old, step;

    if (e->enabled == 0) return 0;
    old = v = *e->val;
    if (a->flags & 8)
        step = e->step2;
    else
        step = e->step;
    if (a->pad & 0x8000) v -= step;
    if (a->pad & 0x2000) v += step;
    if (v < e->min) v = e->max;
    if ((short)e->max < v) v = e->min;
    if (v != old) {
        *e->val = v;
        a->sel = 1;
        a->slot[row].handle = func_00374AE0(a->slot[row].id);
        return 1;
    }
    return 0;
}
