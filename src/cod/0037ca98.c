extern char D_005FEE00[];
extern unsigned short D_0076C8C0;

__attribute__((section(".text.func_0037CA98")))
void func_0037CA98(void)
{
    unsigned short *entry = &D_0076C8C0;
    unsigned int sentinel = 0xFFFFFFFFU;
    int count;
    unsigned int value;
    count = 0x32;
    do {
        if (*entry != 0) {
            value = *(unsigned int *)((char *)entry + 0xC);
            if (value != sentinel)
                *(unsigned int *)((char *)entry + 0xC) = value + 1;
        }
        entry = (unsigned short *)((char *)entry + 0x20);
        count -= 1;
    } while (count >= 0);
}
