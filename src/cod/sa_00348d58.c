/* cygnus-2.96, -freorder-blocks dropped: func_00348D58, clear the pending flag at +0x1AC once acknowledged, step, and set state 2
 * when the sound at +0x3C reports 4 or 6. */
extern int func_00348FF0(char *self);
extern void func_00348DD8(char *self);
extern int func_00359E80(int snd);

__attribute__((section(".text.func_00348D58")))
void func_00348D58(char *self)
{
    int pending = *(int *)(self + 0x1AC);
    int snd = *(int *)(self + 0x3C);
    int st;

    if (pending == 1 && func_00348FF0(self) == pending)
        *(int *)(self + 0x1AC) = 0;
    func_00348DD8(self);
    st = func_00359E80(snd);
    if (st == 4 || st == 6)
        *(int *)(self + 0x4) = 2;
}
