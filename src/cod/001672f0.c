extern char D_00569B70[];
extern char D_005E85F8;
extern char D_005FEE00[];
extern void cCoreSave_clearStateBit0(void *);
extern void SetGlobalToggle_375700(int);

__attribute__((section(".text.func_001672F0")))
void func_001672F0(void)
{
    cCoreSave_clearStateBit0(D_00569B70);
    SetGlobalToggle_375700(1);
    D_005E85F8 = 1;
}
