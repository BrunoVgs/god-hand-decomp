/* Batch 36: unique SN ~104–140 (scratch-only). */
extern void func_002B41F0(void *self);
extern int func_002B4228(void *self);
extern void func_002B42F0(void *self);
extern void func_0037D820(void *self);
extern void func_00378070(void *p);
extern void displayScrollLayer(void *a0, int a1);

__attribute__((section(".text.func_0037CC78")))
void func_0037CC78(unsigned short *self)
{
    unsigned short f = self[0];
    if ((f & 0x40) == 0)
        return;
    if (*(short *)((char *)self + 0x30) == *(short *)((char *)self + 0x32)) {
        self[0] = f | 0x20;
        func_0037D820(self);
        return;
    }
    func_00378070((char *)self + 0x30);
    self[3] = self[3] | 0x9;
}

__attribute__((section(".text.func_003A9538")))
int func_003A9538(signed char *s, int len)
{
    signed char *p;
    signed char zero;
    signed char nine;
    if (len <= 0)
        goto done;
    len -= 1;
    p = s + len;
    if (*p < 0x35)
        goto done;
    zero = 0x30;
    nine = 0x39;
    *p = zero;
    for (;;) {
        len -= 1;
        p -= 1;
        if (len <= 0)
            break;
        if (*p != nine)
            break;
        *p = zero;
    }
    s += len;
    if (*s == 0x39)
        return 0;
    *s = *s + 1;
done:
    return 1;
}
