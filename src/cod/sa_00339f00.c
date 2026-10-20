/* cygnus-2.96: func_00339F00, how many of want bytes are available in lane 0 (free) or lane 1 (data)
 * of the ring buffer; any other lane goes to the error callback. Returns 1 when all are. */
extern int D_00455B88;
extern int D_00455A80;
extern int D_00455B98;
extern int D_00455AB0;
extern int func_00339458(void *a0, void *a1);

typedef struct SjRbf {
    int field_0;
    int open;                   /* 0x04 */
    int field_8;
    int data;                   /* 0x0C */
    int free;                   /* 0x10 */
    int freePos;                /* 0x14 */
    int dataPos;                /* 0x18 */
    int field_1C;
    int size;                   /* 0x20 */
    int extra;                  /* 0x24 */
    char unk28[0x10];
    void (*err)(int, int);      /* 0x38 */
    int errArg;                 /* 0x3C */
} SjRbf;

__attribute__((section(".text.func_00339F00")))
int func_00339F00(SjRbf *r, int lane, int want, int *got)
{
    int n, len;

    if (r == 0) {
        func_00339458(&D_00455B88, &D_00455A80);
        return 0;
    }
    if (r->open == 0) {
        func_00339458(&D_00455B98, &D_00455AB0);
        return 0;
    }
    if (lane == 0) {
        n = r->size - r->freePos + r->extra;
        if (r->free < n)
            n = r->free;
        n = n < want ? n : want;
    } else if (lane == 1) {
        n = r->size - r->dataPos + r->extra;
        if (r->data < n)
            n = r->data;
        n = n < want ? n : want;
    } else {
        n = 0;
        if (r->err != 0)
            r->err(r->errArg, -3);
    }
    *got = n;
    return n == want;
}
