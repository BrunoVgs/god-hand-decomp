
__attribute__((section(".text.cEm00_ckDown")))
int cEm00_ckDown(char *self)
{
    unsigned long value;
    int result;
    if ((*(unsigned short *)(self + 0x3AC) & 8) == 0)
        return 0;
    result = 1;
    value = *(unsigned long *)(self + 0x2F0);
    if ((value & 0xFFFF00000000UL) == 0x20200000000UL)
        result = 0;
    return result;
}
