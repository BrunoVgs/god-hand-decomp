/* Batch 44: unique SN ~128–132 (scratch-only). */

extern void func_0037C6A0(void *slot);
extern void func_0037D3C8(void *slot);
extern void arrayFree(void *self);

__attribute__((section(".text.func_0037C228")))
void func_0037C228(char *dst, char *src)
{
    char *s0 = dst;
    char *s1 = src;

    *(short *)(s0 + 0x30) = 0x7F00;
    *(short *)(s0 + 0x32) = 0;
    *(short *)(s0 + 0x34) = 0;
    *(short *)(s0 + 0x36) = 0;
    *(short *)(s0 + 0x38) = *(unsigned short *)(s1 + 0x30);
    *(short *)(s0 + 0x3A) = *(unsigned short *)(s1 + 0x32);
    if (s1[0xD] & 8)
        func_0037C6A0(s0);
    *(short *)(s0 + 0x26) = *(unsigned short *)(s1 + 0x18);
    *(short *)(s0 + 0x28) = *(unsigned short *)(s1 + 0x1A);
    func_0037D3C8(s0);
}
