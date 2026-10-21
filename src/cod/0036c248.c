extern void *func_0036C2A0(void);
extern void func_0036C438(void *, int);
extern void *func_0036C2F0(void *);
extern int func_0036C670(void *);

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
