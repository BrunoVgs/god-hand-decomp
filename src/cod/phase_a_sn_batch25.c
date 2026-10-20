/* Batch 25: SN exact clone pairs (264–268). Matched only. */
extern int ClearField5B4IfFlagUnset_1B76B0(int a0);
extern void func_001B76D8(void *a0);

struct Entry_b25_264 {
    short f0;
    unsigned short type;
    unsigned short f4;
    short f6;
};
struct Table_b25_264 {
    struct Entry_b25_264 e[4];
};

extern struct Table_b25_264 D_004235D0;
extern struct Table_b25_264 D_004297B8;

extern void func_003823E0(void *a0, char *p, unsigned char flag);
extern void func_00383C70(void *a0, char *p, unsigned char flag);

__attribute__((section(".text.func_003822D0")))
void func_003822D0(char *self, char *ctrl, unsigned char flag)
{
    char *sub = self + 0x318;
    unsigned char f = flag;
    short *slot;
    short c;
    unsigned short u;
    int lim;

    if (f != 0)
        slot = (short *)(sub + (*(unsigned char *)(sub + 2) * 2 + 0x22));
    else
        slot = (short *)(sub + (*(unsigned char *)(sub + 2) * 2 + 0x18));

    lim = -0x80;
    if ((*(int *)(ctrl + 0x38) & 0x8000) != 0) {
        c = *slot;
        u = *(unsigned short *)slot;
        if (c != lim)
            goto dec_check;
        *slot = 0xF;
        goto do_dec_call;
    dec_check:
        if (c < -0xE)
            goto clamp_lo;
        *slot = u - 1;
        goto do_dec_call;
    clamp_lo:
        *slot = lim;
    do_dec_call:
        func_003823E0(self, sub, f);
    }
    lim = -0x80;
    if ((*(int *)(ctrl + 0x38) & 0x2000) != 0) {
        c = *slot;
        u = *(unsigned short *)slot;
        if (c != lim)
            goto inc_check;
        *slot = -0xF;
        goto do_inc_call;
    inc_check:
        if (c >= 0xF)
            goto clamp_hi;
        *slot = u + 1;
        goto do_inc_call;
    clamp_hi:
        *slot = lim;
    do_inc_call:
        func_003823E0(self, sub, f);
    }
}

__attribute__((section(".text.func_00383B60")))
void func_00383B60(char *self, char *ctrl, unsigned char flag)
{
    char *sub = self + 0x370;
    unsigned char f = flag;
    short *slot;
    short c;
    unsigned short u;
    int lim;

    if (f != 0)
        slot = (short *)(sub + (*(unsigned char *)(sub + 4) * 2 + 0x26));
    else
        slot = (short *)(sub + (*(unsigned char *)(sub + 4) * 2 + 0x1C));

    lim = -0x80;
    if ((*(int *)(ctrl + 0x38) & 0x8000) != 0) {
        c = *slot;
        u = *(unsigned short *)slot;
        if (c != lim)
            goto dec_check2;
        *slot = 0xF;
        goto do_dec_call2;
    dec_check2:
        if (c < -0xE)
            goto clamp_lo2;
        *slot = u - 1;
        goto do_dec_call2;
    clamp_lo2:
        *slot = lim;
    do_dec_call2:
        func_00383C70(self, sub, f);
    }
    lim = -0x80;
    if ((*(int *)(ctrl + 0x38) & 0x2000) != 0) {
        c = *slot;
        u = *(unsigned short *)slot;
        if (c != lim)
            goto inc_check2;
        *slot = -0xF;
        goto do_inc_call2;
    inc_check2:
        if (c >= 0xF)
            goto clamp_hi2;
        *slot = u + 1;
        goto do_inc_call2;
    clamp_hi2:
        *slot = lim;
    do_inc_call2:
        func_00383C70(self, sub, f);
    }
}
