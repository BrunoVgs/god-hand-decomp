extern char D_005FEE00[];
extern int cIDBase_trans(void *);

__attribute__((section(".text.func_001F2990")))
void func_001F2990(char *self)
{
    cIDBase_trans(self + 0x10);
    cIDBase_trans(self + 0x930);
}
