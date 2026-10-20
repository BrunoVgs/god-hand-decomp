/* sn-2.95.3-136 matched 60-byte Phase A functions.
 * The extra parameters are the caller's a1/a2/a3, forwarded unchanged
 * into the first call. That keeps the saved argument in s1 and the
 * result in s0. */
extern int func_00373D90(void *a0, int a1, void *a2, int a3);
extern void func_00373FC8(void *a0);
extern int func_00374360(void *a0, int a1, void *a2);
extern void func_00374598(void *a0);

__attribute__((section(".text.func_00373F38")))
int func_00373F38(void *a0, int a1, void *a2, int a3)
{
    int ret = func_00373D90(a0, a1, a2, a3);
    func_00373FC8(a0);
    return ret;
}

__attribute__((section(".text.func_00374508")))
int func_00374508(void *a0, int a1, void *a2)
{
    int ret = func_00374360(a0, a1, a2);
    func_00374598(a0);
    return ret;
}
