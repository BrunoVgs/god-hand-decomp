/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
extern unsigned int strlen(const char *s);
extern void *func_003A5148(void *d, const void *s, unsigned int n);
extern char D_00756080[];

__attribute__((section(".text.func_00330A68")))
void func_00330A68(char *dst)
{
    int len = strlen(D_00756080);

    if (D_00756080[0] == 0) {
        *dst = 0;
    } else {
        func_003A5148(dst, D_00756080, len + 1);
    }
}
