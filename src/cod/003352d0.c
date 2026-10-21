/* cygnus-2.96 matched TU. */

extern char D_003DA4A0[];   /* device name prefix buffer */
extern char D_00454BB0[];   /* "host:" */
extern void func_003A57C4(char *dst, const char *src);   /* strcpy */

#define DEV_NAME_DEFAULT_LEN  6   /* sizeof "host:" */

/* Set the device name prefix; a null name restores the default "host:". */
__attribute__((section(".text.setDevName")))
void setDevName(char *name) {
    if (!__builtin_expect((int)name, 0)) {
        __builtin_memcpy(D_003DA4A0, D_00454BB0, DEV_NAME_DEFAULT_LEN);
    } else {
        func_003A57C4(D_003DA4A0, name);
    }
}
