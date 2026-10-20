/* cygnus-2.96: Sofdec timer step, measures the decode time of one unit (0x3537C0). */
extern void func_003538B0(char *h);
extern int func_0033A010(char *a0, int a1, int a2);
extern int func_00369FB8(char *a0, char *a1);
extern int func_00351C18(char *h, int a1, int a2, int a3);
extern void func_00351B70(char *h, int a1);
extern void func_00358768(char *h, int a1, int a2);

__attribute__((section(".text.func_003537C0")))
int func_003537C0(char *h, char *tm)
{
    char *w;
    char *obj;
    char *sub;
    int t0;
    int r;
    int dt;
    int ret;

    w = *(char **)(h + 0x1FC0);
    obj = *(char **)w;
    func_003538B0(h);
    t0 = func_0033A010(tm, 0, 1);
    sub = w + 0x8C;
    r = func_00369FB8(obj, tm);
    dt = func_0033A010(tm, 0, 1) - t0;
    ret = func_00351C18(h, r, dt, 0xFF000F07);
    func_00351B70(h, dt);
    if (ret == 0) {
        if (*(signed char *)(sub + 0x58) == 0) {
            *(int *)(w + 0x16C) = 1;
        }
        func_00358768(h, 1, *(int *)(sub + 0x18));
        return 0;
    }
    return ret;
}
