extern int func_00373D90(void *a0, int a1, void *a2, int a3);
extern void func_00373FC8(void *a0);

__attribute__((section(".text.func_00373F38")))
int func_00373F38(void *a0, int a1, void *a2, int a3)
{
    int ret = func_00373D90(a0, a1, a2, a3);
    func_00373FC8(a0);
    return ret;
}
