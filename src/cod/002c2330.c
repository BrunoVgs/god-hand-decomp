extern char D_005FEE00[];
extern void *D_003C2F84;
extern int ForwardEntityAndExit_2C2368(void);
extern void cScenario_taskExec(void *, void *, void *, int);

__attribute__((section(".text.func_002C2330")))
int func_002C2330(void *p)
{
    cScenario_taskExec(
        D_003C2F84, (void *)ForwardEntityAndExit_2C2368, p, 1);
    return 1;
}
