extern char D_005FEE00[];

__attribute__((section(".text.func_00306ED8")))
int func_00306ED8(char *self, int index)
{
    char *entry;
    int value;
    if (index < 0x20) {
        entry = *(char **)(self + (index << 2) + 0x300);
        if (entry != 0)
            goto found;
    }
    return -1;
found:
    value = *(unsigned short *)(entry + 0xA) + 1;
    *(unsigned short *)(entry + 0xA) = value;
    return (short)value;
}
