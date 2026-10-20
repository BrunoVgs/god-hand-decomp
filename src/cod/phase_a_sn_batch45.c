/* Batch 45: unique SN ~144–160 (scratch-only). */

extern int func_00374AE0(int a0);
extern char D_0076A7D4[];

__attribute__((section(".text.func_00377CB8")))
void func_00377CB8(void)
{
    char *s0 = D_0076A7D4;
    int s1 = 0x001F0000;
    int s2 = 0;
    int s3 = 0x80;
    int s4;
    int s5;

    s1 |= 0xFFFF;
    s5 = 1;
    s4 = 0xFFFE0000;
    do {
        *(int *)(s0 + 0xC) = s1;
        *(short *)(s0 + 0) = s5;
        s1 = s1 + s4;
        *(short *)(s0 + 4) = s3;
        *(short *)(s0 + 6) = s3;
        *(short *)(s0 + 8) = 0;
        *(short *)(s0 + 0xA) = 0;
        *(int *)(s0 + 0x10) = func_00374AE0(1);
        *(short *)(s0 + 0x14) = s2;
        s2 = s2 + 1;
        s0 = s0 + 0x20;
    } while (s2 < 2);
}
