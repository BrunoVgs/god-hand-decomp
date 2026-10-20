/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_002D4248, split from src/cod/batch36_nm.c by the NM closer. */
extern int func_003447A8(void *a0, void *a1, void *a2);
extern int func_00344E88(int a0, int a1);

__attribute__((section(".text.func_002D4248")))
int func_002D4248(char *self)
{
    int cur;
    int last;
    if (func_003447A8(*(void **)self, self + 0x58, *(void **)(self + 8)) != 1)
        return 0;
    cur = *(int *)(self + 0x58);
    last = *(int *)(self + 0x5C);
    if (cur == last)
        return 1;
    if (last < 0)
        goto neg;
    func_00344E88(*(int *)self, last);
    cur = *(int *)(self + 0x58);
neg:
    *(int *)(self + 0x5C) = cur;
    return 1;
}
