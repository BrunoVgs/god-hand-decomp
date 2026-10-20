extern char D_00583F20[];
extern int GetField_110C_2019F8(char *);
extern void func_0031A808(void *);

__attribute__((section(".text.func_002BE200")))
void func_002BE200(void *self)
{
    if (GetField_110C_2019F8(D_00583F20) == 0)
        func_0031A808(self);
}
