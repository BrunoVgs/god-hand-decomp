extern char D_005FEE00[];
extern void ClearFields_1614D0(void *);

__attribute__((section(".text.func_00167F70")))
void func_00167F70(char *self)
{
    ClearFields_1614D0(self);
    self[0x5A] = 0;
    self[0x5B] = 0;
    self[0x5C] = 0;
    self[0x5D] = 0;
    self[0x90] = 0;
}
