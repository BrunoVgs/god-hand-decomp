/* Cygnus helper requiring the compiler's original block order. */

extern int func_003B9DE0(void *);
extern char D_00460928[];

__attribute__((section(".text.func_003BA088")))
void func_003BA088(char *self)
{
    if (self == 0) {
        func_003B9DE0(D_00460928);
        return;
    }
    *(int *)(self + 0x24) = 1;
}
