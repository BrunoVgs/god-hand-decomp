/* cygnus-2.96 matched TU. */

extern char D_003DA4A0[];
extern char D_00454BB0[];
extern void func_003A57C4(char *dst, const char *src);

__attribute__((section(".text.func_003352D0")))
void func_003352D0(char *name) {
    if (!__builtin_expect((int)name, 0)) {
        __builtin_memcpy(D_003DA4A0, D_00454BB0, 6);
    } else {
        func_003A57C4(D_003DA4A0, name);
    }
}
