/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
extern int D_003EC7DC;
extern char D_00459378[];
extern void MWSFSVM_Error(char *msg);
extern int func_00349720(volatile int *hn);
extern int MWSFD_GetReqSvrBdrLib(void);
extern int func_00349630(volatile int *hn);

__attribute__((section(".text.func_00349590")))
int func_00349590(volatile int *hn)
{
    int st;

    if (D_003EC7DC != 1)
        return 0;
    if (hn == 0) {
        MWSFSVM_Error(D_00459378);
        return 0;
    }
    st = *hn;
    if (st != D_003EC7DC)
        return 0;
    if (func_00349720(hn) == st)
        return 0;
    if (MWSFD_GetReqSvrBdrLib() == st)
        return 0;
    return func_00349630(hn);
}
