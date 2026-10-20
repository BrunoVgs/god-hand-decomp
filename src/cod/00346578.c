/* Cygnus helper requiring the compiler's original block order. */

extern int D_003EE084;
extern void MWSPR_RestoreSprMem(void);
extern void func_003465B8(void);

__attribute__((section(".text.func_00346578")))
int func_00346578(void *a0, int a1, int a2)
{
    if (D_003EE084 == 0)
        MWSPR_RestoreSprMem();
    else
        func_003465B8();
}
