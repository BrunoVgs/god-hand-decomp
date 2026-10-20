/* cygnus-2.96 matched 88-byte Phase A functions. */

extern void func_003562F8(void *);
extern int D_003EE330;
extern void func_0035FEE8(void);
extern void func_0036CAA8(void);
extern void func_0035FE78(void);
extern void func_00360CC8(void);
extern void *func_0036C2A0(void);
extern void func_0036C438(void *, int);
extern void *func_0036C2F0(void *);
extern int func_0036C670(void *);

__attribute__((section(".text.func_00356988")))
void func_00356988(char *self, int value)
{
    char *base = *(char **)(self + 0x1FC0);
    char *slot = base + 0x1128;
    if (*(int *)(slot + 0x1C) != 1) {
        func_003562F8(base + 0x1198);
        *(int *)(slot + 0x1C) = 1;
        *(int *)(slot + 0x20) = value;
    }
}

__attribute__((section(".text.func_0035F900")))
void func_0035F900(void)
{
    if (D_003EE330 > 0) {
        func_0035FEE8();
        func_0036CAA8();
        func_0035FE78();
        func_00360CC8();
        D_003EE330 -= 1;
    }
}

__attribute__((section(".text.func_0036C248")))
void *func_0036C248(void)
{
    void *object = func_0036C2A0();
    if (object == 0)
        return 0;
    func_0036C438(object, 0x40C);
    object = func_0036C2F0(object);
    *(int *)((char *)object + 0x3B4) = func_0036C670(object);
    return object;
}
