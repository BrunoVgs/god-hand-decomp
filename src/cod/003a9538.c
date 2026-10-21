/* sn-2.95.3-136 matched TU. */

/* Round the n-digit decimal string digits to n - 1 digits: when the last digit is
   5 or more, zero it and carry into the digits before it. Returns 0 when the
   carry runs off a leading 9, else 1. */
__attribute__((section(".text.func_003A9538")))
int func_003A9538(char *digits, int n) {
    char *d;

    if (n > 0) {
        n--;
        d = &digits[n];
        if (*d >= '5') {
            do {
                *d-- = '0';
            } while (--n > 0 && *d == '9');
            if (digits[n] == '9') {
                return 0;
            }
            digits[n]++;
        }
    }
    return 1;
}
