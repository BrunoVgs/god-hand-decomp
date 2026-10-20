extern char D_005FEE00[];
extern void UpdateObjWithVtableDispatch_2BB1F0(void *);
extern int func_002B8A30(void *, int);
extern int D_005E8040;

__attribute__((section(".text.func_002B8A70")))
void func_002B8A70(char *self, int value)
{
    *(int *)(self + 0x10) = value;
    self[0xC] = (char)func_002B8A30(&D_005E8040, value);
}

__attribute__((section(".text.func_002B8AA8")))
void func_002B8AA8(int *p)
{
    int active;
    p[0x36] = 0;
    active = (p[0] & 0x203) == 3;
    if (active)
        UpdateObjWithVtableDispatch_2BB1F0((void *)p[0xD]);
}
