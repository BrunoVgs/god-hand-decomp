/* sn-2.95.3-136 matched TU. */

__attribute__((section(".text.func_003A9538")))
int func_003A9538(char *s, int n) {
    char *p;

    if (n > 0) {
        n--;
        p = &s[n];
        if (*p >= '5') {
            do {
                *p-- = '0';
            } while (--n > 0 && *p == '9');
            if (s[n] == '9') {
                return 0;
            }
            s[n]++;
        }
    }
    return 1;
}
