extern int func_0032DC58(void *p);
extern void func_0032E040(void *p, int v);

__attribute__((section(".text.func_00381DC0")))
void func_00381DC0(int unused, char *obj, unsigned char *flag)
{
    void *p = *(void **)(obj + 0x20);
    int r;

    if (p == 0)
        return;
    r = func_0032DC58(p);
    if (r == 0)
        return;
    if (r == 3)
        return;
    if (r == 4)
        return;
    *flag ^= 1;
    func_0032E040(*(void **)(obj + 0x20), *flag);
}
