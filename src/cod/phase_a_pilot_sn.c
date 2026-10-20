extern char D_003FA998[];
extern char *func_003A95A8(char *s);

__attribute__((section(".text.func_003A9620")))
char *func_003A9620(int value, char *str, int base)
{
    unsigned int u;
    int neg;
    int i;

    u = (unsigned int)value;
    neg = (int)(u >> 31);
    if (neg) {
        if (base == 10)
            u = 0u - u;
    }
    i = 0;
    do {
        str[i] = D_003FA998[u % (unsigned int)base];
        u = u / (unsigned int)base;
        i = i + 1;
    } while (u != 0);
    if (neg) {
        str[i] = '-';
        i = i + 1;
    }
    str[i] = 0;
    return func_003A95A8(str);
}

extern int func_0031D098(void *p);
extern int irand(void);
extern void func_00300EF8(
    void *a0, void *a1, int a2, void *a3,
    int t0, int t1, int t2, int t3,
    int s0, int s1, int s2, int s3, int s4);

__attribute__((section(".text.func_00300E30")))
void func_00300E30(char *self, void *other)
{
    char *obj;
    int rnd;
    unsigned int span;
    unsigned short whole;

    obj = *(char **)(self + 0x100);
    if (*(unsigned char *)(obj + 0x28E) != 0) {
        rnd = func_0031D098(self + 0x220);
        *(int *)(self + 0x220) = rnd;
    } else {
        rnd = irand();
        *(int *)(self + 0x220) = rnd;
    }
    whole = *(unsigned short *)(self + 0x224);
    span = 0;
    if (whole != 0) {
        float f;
        int cut;

        f = *(float *)(self + 0x228);
        cut = (int)f;
        span = (whole - cut) & 0xFFFF;
        if (span == 0)
            span = 1;
    }
    func_00300EF8(
        other,
        self,
        *(int *)(self + 0x100),
        self + 0x1A0,
        *(unsigned short *)(self + 0x18E),
        *(int *)(self + 0x108),
        *(int *)(self + 0x10C),
        *(int *)(self + 0x110),
        *(int *)(self + 0x118),
        *(short *)(self + 0x18C),
        *(int *)(self + 0x114),
        *(int *)(self + 0x220),
        (int)span);
}
