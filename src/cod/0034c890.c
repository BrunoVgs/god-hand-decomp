/* cygnus-2.96 matched TU. */

/* The output is a 32-bit pointer, as used by the callers. */
extern int func_0034DD70(char *a0, int error);

__attribute__((section(".text.func_0034C890")))
int func_0034C890(char *a0, int a1, void **a2) {
    char *base = a0 + 0x1310;
    int *p = (int *)(base + a1 * 0x74);

    *a2 = 0;
    if (__builtin_expect(p[1], 0) == 0)
        return func_0034DD70(a0, 0xFF000401);
    *a2 = *(void **)(p + 5);
    return 0;
}
