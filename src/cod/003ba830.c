/* cygnus-2.96 */

extern void func_003B9DE0(void *);
extern char D_00460AD0[];
extern char D_00460AF8[];

__attribute__((section(".text.func_003BA830")))
void func_003BA830(char *self, int *out_a, int *out_b)
{
    if (self == 0) {
        func_003B9DE0(D_00460AD0);
        return;
    }
    if (out_a != 0)
        *out_a = *(int *)(self + 0x1C);
    if (out_b != 0)
        *out_b = *(int *)(self + 0x20);
}

__attribute__((section(".text.func_003BA878")))
void func_003BA878(char *self, int *out_a, int *out_b)
{
    if (self == 0) {
        func_003B9DE0(D_00460AF8);
        return;
    }
    if (out_a != 0)
        *out_a = *(int *)(self + 0x10);
    if (out_b != 0)
        *out_b = *(int *)(self + 0x14);
}
