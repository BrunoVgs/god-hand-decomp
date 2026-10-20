/* sn-2.95.3-136: NM closer handoff. */
typedef struct MenuPageTbl {
    short count;
    char pad2[0x12];
    short count14;
    char pad16[0xA];
} MenuPageTbl;

typedef struct MenuCursor {
    char pad0[7];
    signed char page;
    char pad8[0xE];
    short list[3];
    short pos[8];
    int flags;
    char pad30[8];
    int buttons;
} MenuCursor;

extern MenuPageTbl D_0076DF10[];
extern MenuPageTbl D_0076E510[];
extern MenuPageTbl D_0076EA50[];

__attribute__((section(".text.func_00379F00")))
int func_00379F00(MenuCursor *c)
{
    short max;
    short id;
    short pos;
    short old;
    short *pp;
    short *base;
    int btn;
    int step;

    max = 0;
    id = c->list[c->page];
    switch (c->page) {
    case 0:
        max = D_0076DF10[id].count;
        break;
    case 1:
        max = D_0076E510[id].count;
        break;
    case 2:
        max = D_0076EA50[id].count14;
        break;
    }
    btn = c->buttons;
    base = c->pos;
    pp = &base[c->page];
    pos = *pp;
    old = pos;
    step = (c->flags & 8) ? 10 : 1;
    if (btn & 0x80000001)
        pos -= step;
    if (btn & 0x40000002)
        pos += step;
    if (pos < 0)
        pos = max - 1;
    if (pos >= max)
        pos = 0;
    if (pos != old) {
        *pp = pos;
        return 1;
    }
    return 0;
}
