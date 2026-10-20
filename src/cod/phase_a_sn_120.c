extern char D_0076E590[];
extern char D_0076B9C0[];
extern void func_003772D8(void *ent);
extern void func_00376F18(void *ent);
extern void func_0037C330(void *ent);
extern void func_0037BF10(void *ent);

__attribute__((section(".text.func_00376EA0")))
void func_00376EA0(void)
{
    int p = (int)D_0076E590;
    int end = p + 0x380;

    do {
        if (*(unsigned short *)p != 0) {
            if ((*(unsigned char *)(p + 8) & 0x10) != 0) {
                __asm__ __volatile__("");
                func_003772D8((void *)p);
            } else {
                __asm__ __volatile__("");
                func_00376F18((void *)p);
            }
            *(unsigned short *)p = 0;
        }
        p += 0x70;
    } while (p < end);
}

__attribute__((section(".text.func_0037BE98")))
void func_0037BE98(void)
{
    int p = (int)D_0076B9C0;
    int end = p + 0xF00;

    do {
        if (*(unsigned short *)p != 0) {
            if ((*(unsigned char *)(p + 0xC) & 0x10) != 0) {
                __asm__ __volatile__("");
                func_0037C330((void *)p);
            } else {
                __asm__ __volatile__("");
                func_0037BF10((void *)p);
            }
            *(unsigned short *)p = 0;
        }
        p += 0x50;
    } while (p < end);
}
