/* cygnus-2.96 matched TU. */

extern int func_0035C2D0(void *a0, int a1, int a2, int a3, int t0);

__attribute__((section(".text.func_0034C930")))
int func_0034C930(void *a0, int a1, int a2, int a3) {
    char *base = (char *)a0 + 0x1310;
    int *t1 = (int *)(base + a1 * 0x74);
    if (!__builtin_expect(t1[1], 0))
        return func_0035C2D0(a0, t1[0x13], 0xB, a2, a3);
    return 0;
}
