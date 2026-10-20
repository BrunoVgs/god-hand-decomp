/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
extern long func_003554E8(char *self);

__attribute__((section(".text.func_00350BE8")))
int func_00350BE8(char *self, int mode)
{
    if (func_003554E8(self) == 0)
        return 0;
    if (mode == 0)
        return 1;
    if (*(int *)(self + 0x58) != 1 || mode != 1 || *(int *)(self + 0x968) <= *(int *)(self + 0x96C))
        return 0;
    return 1;
}
