/* cygnus-2.96: func_0032F330, take a free one of the four 0x1964-byte decoder slots, clear it and
 * copy in n stream handles; returns the slot, or 0 when all four are in use. */
typedef struct Slot32F330 {
    signed char used;           /* 0x00 */
    signed char unk01;          /* 0x01 */
    signed char n;              /* 0x02 */
    signed char unk03;          /* 0x03 */
    signed char unk04;          /* 0x04 */
    char unk05[0x17];
    int arg;                    /* 0x1C */
    int h[(0x1964 - 0x20) / 4]; /* 0x20 */
} Slot32F330;

extern void func_003A52F0(void *dst, int c, int n);
extern Slot32F330 D_003D1E70[4];

__attribute__((section(".text.func_0032F330")))
Slot32F330 *func_0032F330(int n, int arg, int *h)
{
    Slot32F330 *s;
    int i;

    for (i = 0; i < 4; i++) {
        if (D_003D1E70[i].used == 0)
            break;
    }
    if (i == 4)
        return 0;
    s = &D_003D1E70[i];
    func_003A52F0(s, 0, sizeof(Slot32F330));
    s->unk01 = 0;
    s->arg = arg;
    for (i = 0; i < n; i++)
        s->h[i] = h[i];
    s->n = n;
    s->unk03 = 0;
    s->unk04 = 0;
    s->used = 1;
    return s;
}
