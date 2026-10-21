extern void func_003823E0(void *a0, char *p, unsigned char flag);

__attribute__((section(".text.func_003822D0")))
void func_003822D0(char *self, char *ctrl, unsigned char flag)
{
    char *sub = self + 0x318;
    short *slot;

    if (flag != 0)
        slot = (short *)(sub + (*(unsigned char *)(sub + 2) * 2 + 0x22));
    else
        slot = (short *)(sub + (*(unsigned char *)(sub + 2) * 2 + 0x18));

    if ((*(int *)(ctrl + 0x38) & 0x8000) != 0) {
        if (*slot == -0x80)
            *slot = 0xF;
        else if (*slot >= -0xE)
            *slot = *slot - 1;
        else
            *slot = -0x80;
        func_003823E0(self, sub, flag);
    }
    if ((*(int *)(ctrl + 0x38) & 0x2000) != 0) {
        if (*slot == -0x80)
            *slot = -0xF;
        else if (*slot < 0xF)
            *slot = *slot + 1;
        else
            *slot = -0x80;
        func_003823E0(self, sub, flag);
    }
}
