/* sn-2.95.3-136 matched TU. */

extern char D_0045D008[];

__attribute__((section(".text.func_00386640")))
int func_00386640(char **arg0) {
    char *p;
    signed char n = -1;
    char c;

    if (((int *)*arg0)[-4] == 0) {
        p = D_0045D008;
    } else {
        (*arg0)[((int *)*arg0)[-4]] = 0;
        p = *arg0;
    }
    while ((c = *p++) != 0) {
        if (c == '/') {
            n++;
        }
    }
    if (n < 0) {
        n = 0;
    }
    return n;
}
