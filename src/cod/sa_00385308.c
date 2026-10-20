/* sn-2.95.3-136: func_00385308, debug-menu stepper for one of two per-channel offsets (-15..15, with
 * -0x80 as off, wrapping through off); pad bit 0x8000 steps down, 0x2000 up, and the voice is updated. */
typedef struct Pad385308 {
    char unk0[0x38];
    int trg;    /* 0x38 */
} Pad385308;

typedef struct Snd385308 {
    char unk0[0x30];
    int voice;  /* 0x30 */
} Snd385308;

extern void func_0032A6D0(int voice, int which, int val);

#define OFF_385308 (-0x80)

__attribute__((section(".text.func_00385308")))
void func_00385308(unsigned char *p, Pad385308 *pad, unsigned char which)
{
    Snd385308 *snd = (Snd385308 *)(p + 0x484);
    short *v;
    int idx;

    if (which) {
        v = (short *)(p + 0x47A);
        idx = 1;
    } else {
        v = (short *)(p + 0x478);
        idx = 0;
    }
    if (pad->trg & 0x8000) {
        if (*v == OFF_385308)
            *v = 15;
        else if (*v >= -14)
            *v = *v - 1;
        else
            *v = OFF_385308;
        if (snd->voice != 0)
            func_0032A6D0(snd->voice, idx, *v);
    }
    if (pad->trg & 0x2000) {
        if (*v == OFF_385308)
            *v = -15;
        else if (*v < 15)
            *v = *v + 1;
        else
            *v = OFF_385308;
        if (snd->voice != 0)
            func_0032A6D0(snd->voice, idx, *v);
    }
}
