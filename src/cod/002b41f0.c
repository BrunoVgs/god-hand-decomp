extern char D_005FEE00[];
extern void func_002B45F0(void *);

__attribute__((section(".text.func_002B41F0")))
void func_002B41F0(char *self)
{
    func_002B45F0(self);
    *(int *)(self + 0x14) &= ~0x10;
    *(int *)(self + 0x10) = 0;
}
