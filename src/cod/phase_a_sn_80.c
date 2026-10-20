/* sn-2.95.3-136 matched 80-byte Phase A functions. */

extern void func_00378C48(void *);
extern void func_0037B0E0(void *);
extern void func_00379190(void *);
extern void func_00379BC0(void *);
extern short func_0037D760(void *);
extern void func_0037D728(void *);
extern void func_00380E10(void *);
extern void func_00381D38(void *, void *, void *);
extern void func_00383438(void *, void *);
extern void func_00380E88(void *, void *, void *);

__attribute__((section(".text.func_00378BF8")))
void func_00378BF8(char *self)
{
    func_00378C48(self);
    func_0037B0E0(self);
    if (self[6] == 0)
        func_00379190(self);
    else
        func_00379BC0(self);
}

__attribute__((section(".text.func_0037C2E0")))
void func_0037C2E0(char *dst, char *src)
{
    *(short *)(dst + 0x46) = func_0037D760(src + 0x20);
    *(unsigned short *)(dst + 0x48) = *(unsigned short *)(src + 0x3C);
    *(unsigned short *)(dst + 0x2E) = *(unsigned short *)(src + 0x1E);
    func_0037D728(dst);
}

__attribute__((section(".text.func_00380DC0")))
void func_00380DC0(char *self)
{
    func_00380E10(self);
    func_00381D38(self, self + 0x348, self + 0x318);
    func_00383438(self, self + 0x370);
    func_00380E88(self, self + 0x484, self + 0x470);
}
