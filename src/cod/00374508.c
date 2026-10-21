extern int func_00374360(void *a0, int a1, void *a2);
extern void func_00374598(void *a0);

__attribute__((section(".text.func_00374508")))
int func_00374508(void *a0, int a1, void *a2)
{
    int ret = func_00374360(a0, a1, a2);
    func_00374598(a0);
    return ret;
}
