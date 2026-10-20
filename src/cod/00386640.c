/* sn-2.95.3-136: func_00386640, depth of a path string (number of '/' minus one, clamped at 0);
 * the string keeps its length at -0x10. */
extern char D_0045D008[];

__attribute__((section(".text.func_00386640")))
int func_00386640(char **str)
{
    char *p;
    char c;
    signed char n = -1;
    int len = ((int *)*str)[-4];

    if (len == 0) {
        p = D_0045D008;
    } else {
        (*str)[len] = 0;
        p = *str;
    }
    while ((c = *p++) != 0) {
        if (c == '/')
            n++;
    }
    if (n < 0)
        n = 0;
    return n;
}
