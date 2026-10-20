typedef struct Blk366EC0 {
    int w[8];
} Blk366EC0;

typedef struct Dec366EC0 {
    char pad0[0x28];
    Blk366EC0 cur;
    Blk366EC0 slot[3];
} Dec366EC0;

extern int func_00366FE0(Dec366EC0 *d, char *p, int len, int *used, int *flags);

__attribute__((section(".text.func_00366EC0")))
int func_00366EC0(Dec366EC0 *d, char *p, int len, int *total, int *flags)
{
    int used;
    int fl;
    int r;
    int idx;
    Blk366EC0 *cur;

    while (len >= 4) {
        r = func_00366FE0(d, p, len, &used, &fl);
        {
            int f0 = *flags;
            int n = used;
            int t0 = *total;
            p += n;
            len -= n;
            *total = t0 + n;
            *flags = f0 | fl;
        }
        if (r == 0)
            break;
    }
    if (*flags & 0x20000) {
        cur = &d->cur;
        idx = 0;
        if (cur->w[2] == 0)
            idx = (cur->w[3] != 0) ? 1 : 2;
        d->slot[idx] = *cur;
    }
    return 0;
}
