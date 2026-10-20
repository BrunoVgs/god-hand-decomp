extern void func_003562F8(void *);

__attribute__((section(".text.func_00356988")))
void func_00356988(char *self, int value)
{
    char *base = *(char **)(self + 0x1FC0);
    char *slot = base + 0x1128;
    if (*(int *)(slot + 0x1C) != 1) {
        func_003562F8(base + 0x1198);
        *(int *)(slot + 0x1C) = 1;
        *(int *)(slot + 0x20) = value;
    }
}
