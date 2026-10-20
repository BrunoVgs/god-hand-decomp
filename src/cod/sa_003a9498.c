/* sn-2.95.3-136: NM closer handoff. */
__attribute__((section(".text.func_003A9498")))
char *func_003A9498(char *s, const char *delim, char **last)
{
    char *spanp;
    int c, sc;
    char *tok;

    if (s == 0 && (s = *last) == 0)
        return 0;
cont:
    c = *s++;
    spanp = (char *)delim;
    if ((sc = *spanp++) != 0) {
        do {
            if (c == sc)
                goto cont;
            sc = *spanp;
            __asm__ volatile("nop");
            spanp++;
        } while (sc != 0);
    }
    if (c == 0) {
        *last = 0;
        return 0;
    }
    tok = s - 1;
    for (;;) {
        c = *s++;
        spanp = (char *)delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0)
                    s = 0;
                else
                    s[-1] = 0;
                *last = s;
                return tok;
            }
        } while (sc != 0);
    }
}
