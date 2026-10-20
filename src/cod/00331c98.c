/* Cygnus helper requiring the compiler's original block order. */

extern int D_003D8480;
extern char D_00454098[];
extern void func_003B1F28(void *);

__attribute__((section(".text.func_00331C98")))
void func_00331C98(int value)
{
    D_003D8480 = value;
    if (value == 1)
        func_003B1F28(D_00454098);
}
