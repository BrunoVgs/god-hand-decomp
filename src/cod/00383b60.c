extern void func_00383C70(void *a0, char *p, unsigned char flag);

__attribute__((section(".text.func_00383B60")))
void func_00383B60(char *self, char *ctrl, unsigned char flag)
{
    char *sub = self + 0x370;
    short *slot;

    if (flag != 0)
        slot = (short *)(sub + (*(unsigned char *)(sub + 4) * 2 + 0x26));
    else
        slot = (short *)(sub + (*(unsigned char *)(sub + 4) * 2 + 0x1C));

    if ((*(int *)(ctrl + 0x38) & 0x8000) != 0) {
        if (*slot == -0x80)
            *slot = 0xF;
        else if (*slot >= -0xE)
            *slot = *slot - 1;
        else
            *slot = -0x80;
        func_00383C70(self, sub, flag);
    }
    if ((*(int *)(ctrl + 0x38) & 0x2000) != 0) {
        if (*slot == -0x80)
            *slot = -0xF;
        else if (*slot < 0xF)
            *slot = *slot + 1;
        else
            *slot = -0x80;
        func_00383C70(self, sub, flag);
    }
}
