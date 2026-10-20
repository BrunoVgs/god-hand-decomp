extern char D_00569B70[];
extern char D_005FEE00[];
extern void cCoreSave_setSkill(void *, int, signed char);

__attribute__((section(".text.func_002C9BB0")))
void func_002C9BB0(int *self, int index, unsigned char value)
{
    if (*self)
        cCoreSave_setSkill(
            D_00569B70, *((signed char *)self + index + 0x14), value);
}

__attribute__((section(".text.func_002C9B78")))
void func_002C9B78(int *p, int a, unsigned char b)
{
    if (*p)
        cCoreSave_setSkill(D_00569B70, a, b);
}

__attribute__((section(".text.func_002C9BF8")))
void func_002C9BF8(int *p, int index)
{
    if (*p)
        cCoreSave_setSkill(
            D_00569B70, *((signed char *)p + index + 0x14), -1);
}
