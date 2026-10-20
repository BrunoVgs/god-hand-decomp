/* sn-2.95.3-136: func_0037A0F0, steps idx by dir (wrapping) through the current column's list until it
 * hits an enabled entry; returns that index, or -1 if none is enabled. */
typedef struct {
    char unk0[7];
    signed char col;
    char unk8[8];
    short count[3]; /* 0x10 */
} MenuColSel;

typedef struct {
    int on;
    char unk4[0x1C];
} MenuColEnt;

typedef struct {
    char unk0[0x14];
    int on; /* 0x14 */
    char unk18[8];
} SelEnt37A0F0b;

extern MenuColEnt D_0076DF10[];
extern MenuColEnt D_0076E510[];
extern SelEnt37A0F0b D_0076EA50[];

__attribute__((section(".text.func_0037A0F0")))
short func_0037A0F0(MenuColSel *o, short idx, short dir)
{
    short n = o->count[o->col];
    short i;

    for (i = 0; i < n; i++) {
        if (idx <= -1)
            idx = n - 1;
        if (idx >= n)
            idx = 0;
        switch (o->col) {
        case 0:
            if (D_0076DF10[idx].on != 0)
                return idx;
            break;
        case 1:
            if (D_0076E510[idx].on != 0)
                return idx;
            break;
        case 2:
            if ((&D_0076EA50[idx])->on != 0)
                return idx;
            break;
        }
        idx += dir;
    }
    return -1;
}
