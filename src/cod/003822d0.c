extern void func_003823E0(void *a0, char *p, unsigned char flag);

__attribute__((section(".text.func_003822D0")))
void func_003822D0(char *self, char *ctrl, unsigned char flag)
{
    char *sub = self + 0x318;
    short *slot;
    short c;
    unsigned short u;
    int lim;

    if (flag != 0)
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
        func_003823E0(self, sub, flag);
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
        func_003823E0(self, sub, flag);
    }
}
