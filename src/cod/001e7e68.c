extern char D_005FEE00[];
extern void func_001E8DF0(void *, void *, void *, unsigned short);

__attribute__((section(".text.func_001E7E68")))
void func_001E7E68(void *a, void *b, void *c, unsigned short d)
{
    if (b != 0 && c != 0 && d < 0x16)
        func_001E8DF0(a, b, c, d);
}
