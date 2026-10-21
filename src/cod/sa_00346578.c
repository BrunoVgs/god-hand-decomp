/* cygnus-2.96 matched TU. */
extern int D_003EE084;
extern int MWSPR_RestoreSprMem(void);
extern int func_003465B8(void);

/* Restore scratchpad memory using the selected DMA mode. */
__attribute__((section(".text.func_00346578")))
int func_00346578(void)
{
    int r;

    if (D_003EE084 == 0) {
        r = MWSPR_RestoreSprMem();
    } else {
        r = func_003465B8();
    }
    return r;
}
