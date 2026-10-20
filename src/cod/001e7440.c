extern char D_005FEE00[];
extern void cIDBase_trans(void *);

__attribute__((section(".text.func_001E7440")))
void func_001E7440(char *self)
{
    cIDBase_trans(self + 0x530);
    cIDBase_trans(self);
}
