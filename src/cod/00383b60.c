extern void func_00383C70(void *a0, char *p, unsigned char flag);

__attribute__((section(".text.func_00383B60")))
void func_00383B60(char *self, char *ctrl, unsigned char flag)
{
    char *sub = self + 0x370;
    short *slot;
    short c;
    unsigned short u;
    int lim;

    if (flag != 0)
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
        func_00383C70(self, sub, flag);
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
        func_00383C70(self, sub, flag);
    }
}
