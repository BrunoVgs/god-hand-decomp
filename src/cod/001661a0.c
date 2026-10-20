extern char D_005FEE00[];
extern void cIDBase_move(void *);

__attribute__((section(".text.func_001661A0")))
void func_001661A0(char *self)
{
    cIDBase_move(self + 0x100);
    cIDBase_move(self + 0x180);
    cIDBase_move(self + 0x230);
}
