extern char D_005FEE00[];
extern void func_00302918(void *);

__attribute__((section(".text.func_003039E8")))
void func_003039E8(int *p, int a, int b)
{
    if (p[0x43] == a && p[0x44] == b)
        func_00302918(p);
}
