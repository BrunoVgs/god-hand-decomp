typedef void (*HandlerFn)(void *, unsigned int, unsigned int, unsigned int);

__attribute__((section(".text.func_0036CC08")))
void func_0036CC08(char *self, int unused, void *arg)
{
    unsigned char x = *(unsigned char *)(self + 0x14);
    unsigned char y = *(unsigned char *)(self + 0x15);
    unsigned char z = *(unsigned char *)(self + 0x16);
    HandlerFn fn = *(HandlerFn *)(self + 0x1C);

    if (fn != 0)
        fn(arg, x, y, z);
}

__attribute__((section(".text.func_0036CC40")))
void func_0036CC40(char *self, int unused, void *arg)
{
    unsigned char x = *(unsigned char *)(self + 0x14);
    unsigned char y = *(unsigned char *)(self + 0x15);
    unsigned char z = *(unsigned char *)(self + 0x16);
    HandlerFn fn = *(HandlerFn *)(self + 0x20);

    if (fn != 0)
        fn(arg, x, y, z);
}
