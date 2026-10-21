/* sn-2.95.3-136 matched TU. */

/* strstr: return the first place s2 occurs in s1, s1 itself for an empty s2,
   or 0. */
__attribute__((section(".text.func_003A93F8")))
char *func_003A93F8(char *s1, char *s2) {
    int i;

    if (*s1 == 0) {
        if (*s2 == 0) {
            return s1;
        }
        return 0;
    }
    goto loop;
found:
    return s1;
loop:
    i = 0;
    if (*s2 == 0) {
        goto found;
    }
    for (; s2[i] == s1[i]; ) {
        i++;
        if (s2[i] == 0) {
            goto found;
        }
    }
    s1++;
    if (*s1 != 0) {
        goto loop;
    }
    return 0;
}
