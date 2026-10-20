/* cygnus-2.96, -freorder-blocks dropped: func_00350718, per-frame movie step: skipped while element 5 is unset or the handle is idle. */
extern int GetArrayElemA0C_35A1C8(char *hn, int i);
extern int func_003508C0(char *hn);
extern void sfmpv_SetCondY16(char *hn);
extern void func_00350820(char *hn);
extern int func_00350C78(char *hn);
extern void func_003508D8(char *hn);
extern void func_00350B60(char *hn);

__attribute__((section(".text.func_00350718")))
int func_00350718(char *hn)
{
    int r = GetArrayElemA0C_35A1C8(hn, 5);
    int res;

    if (r == 0)
        return r;
    if (func_003508C0(hn) == 1)
        return 0;
    sfmpv_SetCondY16(hn);
    if (*(int *)(hn + 0x48) == 2)
        func_00350820(hn);
    res = func_00350C78(hn);
    func_003508D8(hn);
    func_00350B60(hn);
    return res;
}
