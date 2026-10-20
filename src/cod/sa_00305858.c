/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_00305858, split from src/cod/batch44_nm.c by the NM closer. */
extern void func_00306BB0(void *a0, void *a1);
extern void Effect_killByMode(void *a0, int a1);
extern char D_00741DC8[];

__attribute__((section(".text.func_00305858")))
int func_00305858(char *self, int a1)
{
    char *s0 = self;
    int v1 = 0;
    int v0;

    a1 ^= 1;
    v0 = *(int *)(s0 + 0xC) - 1;
    if (a1)
        v1 = v0;
    *(int *)(s0 + 0xC) = v0;
    if (v1 > 0)
        return 0;
    if (v1 != 0)
        return 0;
    func_00306BB0(D_00741DC8, *(void **)s0);
    Effect_killByMode(*(void **)s0, 2);
    *(int *)(s0 + 0xC) = 0;
    *(int *)(s0 + 4) = 0;
    *(int *)(s0 + 8) = 0;
    *(int *)s0 = 5;
    return 1;
}
