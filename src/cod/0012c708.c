extern int SetEffect(int a0, int a1, void *a2, int a3, int t0, unsigned t1);

__attribute__((section(".text.func_0012C708")))
void func_0012C708(char *self)
{
    *(int *)(self + 0x5FC) = 0x258;
    SetEffect(0, 0x4E, self, 0, 5, 0xFFFFFFFFU);
}
