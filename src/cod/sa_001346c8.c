/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_001346C8, split from src/cod/batch27_nm.c by the NM closer. */
__attribute__((section(".text.func_001346C8")))
void *func_001346C8(void *a0, void *a1)
{
    if (a1 == 0)
        return 0;
    a0 = *(void **)a0;
    for (;;) {
        void *k;

        if (a0 == 0)
            break;
        k = *(void **)a0;
        __asm__ volatile("nop" ::: "memory");
        if (k == a1)
            break;
        a0 = *(void **)((char *)a0 + 0x10);
    }
    return a0;
}
