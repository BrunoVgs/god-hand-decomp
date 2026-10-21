/* cygnus-2.96 matched TU. */
extern int D_003EE084;
extern int MWSPR_SaveSprMem(void);
extern int func_003464D8(void);

/* SPR-memory save dispatcher: real save when idle, deferred path otherwise. */
__attribute__((section(".text.func_00346498")))
int func_00346498(void)
{
    int r;

    if (D_003EE084 == 0) {
        r = MWSPR_SaveSprMem();
    } else {
        r = func_003464D8();
    }
    return r;
}
