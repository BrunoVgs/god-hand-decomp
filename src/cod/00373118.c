extern char D_005FEE00[];

__attribute__((section(".text.func_00373118")))
int func_00373118(char *object, int value, char *source, int enabled)
{
    int flags = *(int *)(object + 0x4C);
    *(int *)(object + 0x48) = 1;
    *(int *)(object + 0x74) = value;
    *(int *)(object + 0x7C) = *(int *)(source + 8);
    *(int *)(object + 0x6C) = *(int *)(source + 4);
    *(int *)(object + 0x4C) = flags | 1;
    if (enabled)
        *(int *)(object + 0x4C) |= 0x10;
    return 1;
}
