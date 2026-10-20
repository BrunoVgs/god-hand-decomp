/* Cygnus helper requiring the compiler's original block order. */

extern int D_003EE084;
extern void MWSPR_SaveSprMem(void);
extern void func_003464D8(void);

__attribute__((section(".text.func_00346498")))
int func_00346498(int a0, int a1, void *a2)
{
    if (D_003EE084 == 0)
        MWSPR_SaveSprMem();
    else
        func_003464D8();
}
