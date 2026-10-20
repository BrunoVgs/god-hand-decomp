extern char D_005FEE00[];
extern int func_0037FE78(void *, void *);

__attribute__((section(".text.func_0037FE40")))
void func_0037FE40(unsigned char *self)
{
    if (func_0037FE78(self, self + 0x370))
        self[2] = 1;
}
