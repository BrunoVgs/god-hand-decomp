extern int StoreSoundEntry_3749D8(int index, void *slot);

__attribute__((section(".text.func_0037B768")))
void func_0037B768(char *self)
{
    int index = self[0x27];
    short *slot = (short *)(self + 0x16C + (index << 5));

    *slot = 0;
    StoreSoundEntry_3749D8(self[0x27], slot);
}
