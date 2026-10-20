extern char D_005FEE00[];
extern int StoreSoundEntry_3749D8(int, void *);

__attribute__((section(".text.func_0037B720")))
void func_0037B720(signed char *self)
{
    int index;
    if (self[0x29] == 0)
        return;
    index = self[0x27];
    StoreSoundEntry_3749D8(
        index, (char *)self + 0x16C + (index << 5));
    self[0x29] = 0;
}
