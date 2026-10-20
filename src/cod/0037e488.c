extern char D_005FEE00[];
extern int func_0037E8D8(void *);

__attribute__((section(".text.func_0037E488")))
void func_0037E488(unsigned char *self)
{
    if (func_0037E8D8(self))
        self[2] = 0xC;
    else
        self[2] = 1;
}
