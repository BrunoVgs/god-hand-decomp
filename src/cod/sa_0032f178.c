/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct {
    char pad0[3];
    signed char n;     /* 0x03 */
    void *dec;         /* 0x04 */
    char pad8[4];
    void *strm[1];     /* 0x0C */
} StmSet;

extern int func_0032F468(void *dec);
extern int GuardedCall_00329FD0_329F98(void *s);

__attribute__((section(".text.func_0032F178")))
int func_0032F178(StmSet *p)
{
    int i;
    int r;

    if (func_0032F468(p->dec) != 3)
        goto fail;
    for (i = 0; i < p->n; i++) {
        r = GuardedCall_00329FD0_329F98(p->strm[i]);
        if (r != 5 && r != 0)
            break;
    }
    if (i != p->n)
        goto fail;
    return 1;
fail:
    return 0;
}
