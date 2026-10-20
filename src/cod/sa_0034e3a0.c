/* cygnus-2.96: func_0034E3A0, fetches the current read chunk of the stream; when a new
 * sector-aligned chunk of at least 2 KiB arrives, notifies the read callback once. */
typedef struct {
    char *ptr; /* 0x0 */
    int len; /* 0x4 */
    int pad8;
    int extra; /* 0xC */
    int pad10[4];
} Chunk;
typedef struct {
    char pad0[0x1F84];
    void *sj; /* 0x1F84 */
    char pad1F88[0x37A0 - 0x1F88];
    void (*cb)(void *obj, char *ptr, int len); /* 0x37A0 */
    void *cbobj; /* 0x37A4 */
    int pos; /* 0x37A8 */
    char *last; /* 0x37AC */
} SfdHn;
extern int func_0034C2B8(SfdHn *hn, void *sj, Chunk *ck);

__attribute__((section(".text.func_0034E3A0")))
int func_0034E3A0(SfdHn *hn, char **ptr, int *len, int unused, int *end)
{
    Chunk ck;
    int ret;

    ret = func_0034C2B8(hn, hn->sj, &ck);
    if (ret == 0) {
        *len = ck.len;
        *end = ck.len + ck.extra;
        *ptr = ck.ptr;
        if (*len >= 0x800 && ck.ptr != hn->last && !(hn->pos & 0x7FF)) {
            void (*cb)(void *, char *, int) = hn->cb;
            void *obj = hn->cbobj;
            if (cb != 0)
                cb(obj, ck.ptr, *len);
            hn->last = *ptr;
        }
        return 0;
    }
    return ret;
}
