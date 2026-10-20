extern char D_005FEE00[];
extern void func_0037D680(void *);

__attribute__((section(".text.func_0037C2A8")))
void func_0037C2A8(unsigned char *destination, unsigned char *source)
{
    *(unsigned short *)(destination + 0x40) =
        *(unsigned short *)(source + 0x34);
    *(unsigned short *)(destination + 0x42) =
        *(unsigned short *)(source + 0x36);
    *(unsigned short *)(destination + 0x2C) =
        *(unsigned short *)(source + 0x1C);
    func_0037D680(destination);
}
