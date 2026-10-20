extern void func_002B1F80(
    void *, int, void *, float, float, float, float);

__attribute__((section(".text.func_002B2058")))
void func_002B2058(
    void *a0, int a1, void *a2, float f12, float f13, float f14, float f15)
{
    func_002B1F80(a0, a1, a2, f12, f13, f12 + f14, f13 + f15);
}
