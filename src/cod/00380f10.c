extern int GuardedCall_00329FD0_329F98(void *p);
extern void func_0032B300(void *p, int v);

__attribute__((section(".text.func_00380F10")))
void func_00380F10(int unused, char *obj, unsigned char *flag)
{
    void *p = *(void **)(obj + 0x30);
    int r;

    if (p == 0)
        return;
    r = GuardedCall_00329FD0_329F98(p);
    if (r == 0)
        return;
    if (r == 5)
        return;
    if (r == 6)
        return;
    *flag ^= 1;
    func_0032B300(*(void **)(obj + 0x30), *flag);
}
