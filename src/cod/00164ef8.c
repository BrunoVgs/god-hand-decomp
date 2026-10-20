extern char D_005FEE00[];
extern void ClearFields_1614D0(void *);

__attribute__((section(".text.func_00164EF8")))
void func_00164EF8(char *self)
{
    ClearFields_1614D0(self);
    *(int *)(self + 0x298) = 0;
    self[0x5A] = 0;
    self[0x5B] = 0;
    self[0x5C] = 0;
    self[0x5D] = 0;
}
