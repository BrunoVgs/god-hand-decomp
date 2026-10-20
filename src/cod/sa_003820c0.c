/* sn-2.95.3-136: seed the four sound slots on first use, then play either the current cue (if its slot is idle)
 * or, with no current cue, every idle slot; same shape as func_00383A20. */
extern void func_0032EC78(int h, int slot, int cue);

__attribute__((section(".text.func_003820C0")))
void func_003820C0(int a0, unsigned char *p)
{
    int i;
    int j;
    int k;
    int h;
    int n;
    unsigned char *q;
    unsigned char *r;
    unsigned char *s;
    unsigned char *t;
    unsigned char *u;
    unsigned char *v;
    unsigned short *d1;
    unsigned short *d2;

    q = p + 0x30;
    if (p[2] == 0) {
        i = 0;
        d1 = (unsigned short *)(p + 0x6);
        d2 = (unsigned short *)(p + 0x10);
    copy:
        *d2++ = *(unsigned short *)(p + 0xE);
        *d1++ = *(unsigned short *)(p + 0x4);
        if (++i < 4) {
            /* the extra uses of p in this loop give p priority for s0 over k */
            p++;
            p--;
            goto copy;
        }
    }
    h = *(int *)(q + 0x20);
    if (h == 0) {
        return;
    }
    if (p[2] != 0) {
        n = p[2];
        t = q;
        t += n;
        if (t[0x18] != 0) {
            return;
        }
        u = p;
        u += n * 2;
        func_0032EC78(h, n - 1, *(short *)(u + 4));
    } else {
        for (j = 0; j < *(int *)(q + 8); j++) {
            r = q + 0x18;
            s = p + 4;
            k = j + 1;
            if (r[k] == 0) {
                v = s;
                v += p[2] * 2;
                func_0032EC78(*(int *)(q + 0x20), j, *(short *)v);
            }
        }
    }
}
