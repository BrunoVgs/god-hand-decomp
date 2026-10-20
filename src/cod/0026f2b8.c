extern char D_005FEE00[];

__attribute__((section(".text.func_0026F2B8")))
int func_0026F2B8(unsigned char *p)
{
    unsigned char mode = p[0x2F4];
    if (mode == 1)
        return 1;
    if (mode == 2 && p[0x2F5] != mode)
        return 1;
    return 0;
}
