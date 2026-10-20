/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_001CD7A8, split from src/cod/batch30_nm.c by the NM closer. */

extern void cIDBase_release(void *p);
extern void cHeap_free(void *heap, void *block);
extern char *D_003C2384;
extern int D_00747A84[];
extern void cTaskWork_exit(void *p);
extern char D_0076A790[];
extern int func_0037C388(void *a0);
extern int func_0037C420(void *a0);
extern int func_0037C4C0(void *a0);

__attribute__((section(".text.func_001CD7A8")))
void func_001CD7A8(char *self)
{
    char *other = *(char **)(self + 0x670);
    float *dst;
    float *src;

    if (other == 0)
        return;
    src = *(float **)(other + 0xF0);
    dst = *(float **)(self + 0xF0);
    if (dst != src) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
    }
    (*(float **)(self + 0xF0))[1] -= 0.6f;
}
