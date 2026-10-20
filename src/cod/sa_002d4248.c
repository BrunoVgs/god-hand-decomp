/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_002D4248, split from src/cod/batch36_nm.c by the NM closer. */
extern int func_003447A8(void *a0, void *a1, void *a2);
extern int func_00344E88(int a0, int a1);

__attribute__((section(".text.func_002D4248")))
int func_002D4248(char *self)
{
    char *s0 = self;
    int v0;
    int a1;
    if (func_003447A8(*(void **)s0, s0 + 0x58, *(void **)(s0 + 8)) != 1)
        return 0;
    v0 = *(int *)(s0 + 0x58);
    a1 = *(int *)(s0 + 0x5C);
    if (v0 == a1)
        return 1;
    if (a1 < 0)
        goto neg;
    func_00344E88(*(int *)s0, a1);
    v0 = *(int *)(s0 + 0x58);
neg:
    *(int *)(s0 + 0x5C) = v0;
    return 1;
}
