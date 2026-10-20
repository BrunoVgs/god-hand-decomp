/* sn-2.95.3-136 matched TU. */

__attribute__((section(".text.func_0031CDC0")))
int func_0031CDC0(unsigned int *p, unsigned int *a, unsigned int *b, int idx) {
    int cnt;
    unsigned int i;
    unsigned int n;
    unsigned int *q;
    unsigned int v;

    if (p == 0) {
        return 0;
    }
    n = p[0];
    cnt = 0;
    q = p + n;
    for (i = 1; i <= n; i++) {
        v = *++q;
        if (v == *a || v == *b) {
            if (cnt == idx) {
                return p[i] + (int)p;
            }
            cnt++;
        }
    }
    return 0;
}
