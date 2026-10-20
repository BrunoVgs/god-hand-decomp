extern char D_0044BED0[];
extern void func_002BB018(void *, int);

__attribute__((section(".text.func_002BAFE0")))
void func_002BAFE0(char *self, int flags)
{
    *(char **)(self + 0x100) = D_0044BED0;
    if (flags & 1)
        func_002BB018(self, 0x110);
}
