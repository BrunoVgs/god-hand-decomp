extern char D_005FEE00[];
extern void func_002A9708(void *);

__attribute__((section(".text.func_002A96D8")))
void func_002A96D8(int *p, int a, int b, int c, int d)
{
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    func_002A9708(p);
}
