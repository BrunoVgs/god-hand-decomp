extern short func_0037D760(void *);
extern void func_0037D728(void *);

__attribute__((section(".text.func_0037C2E0")))
void func_0037C2E0(char *dst, char *src)
{
    *(short *)(dst + 0x46) = func_0037D760(src + 0x20);
    *(unsigned short *)(dst + 0x48) = *(unsigned short *)(src + 0x3C);
    *(unsigned short *)(dst + 0x2E) = *(unsigned short *)(src + 0x1E);
    func_0037D728(dst);
}
