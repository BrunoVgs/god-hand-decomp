extern int func_00346DD0(void *, int);
extern int SUD_AnalyTypeCcs(char *, int);

__attribute__((section(".text.func_00346D80")))
int func_00346D80(void *table, char *object)
{
    int ok;
    char *ccs;
    ok = func_00346DD0(table, *(int *)(object + 0x30)) == 1;
    ccs = *(char **)(object + 0x88);
    if (ccs != 0)
        ok = SUD_AnalyTypeCcs(ccs, *(int *)(object + 0x8C)) == 1;
    return ok;
}
