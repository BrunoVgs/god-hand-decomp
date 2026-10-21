extern char D_00569B70[];
extern int cCoreSave_getSkill(void *, int);

__attribute__((section(".text.func_002C9A90")))
int func_002C9A90(int *self, int index)
{
    if (*self == 0)
        return 0;
    return cCoreSave_getSkill(
        D_00569B70, *((signed char *)self + index + 0x14));
}
