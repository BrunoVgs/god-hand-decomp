/* cygnus-2.96: func_003391F8, puts a data chunk back into the memory stream (lane 1 only); a chunk
 * that is not the one just taken, or any other lane, notifies the callback with -3. */
typedef struct { char *data; int len; } Chunk3391F8;
typedef struct {
    int pad0;
    int used;                    /* 0x04 */
    int pad08;
    int data;                    /* 0x0C */
    int free;                    /* 0x10 */
    char *base;                  /* 0x14 */
    int size;                    /* 0x18 */
    void (*cb)(void *obj, int ev); /* 0x1C */
    void *cbobj;                 /* 0x20 */
} SjMem3391F8;

extern void func_00338A48(void *a0, void *a1);
extern int D_00455A10;
extern int D_00455920;
extern int D_00455A20;
extern int D_00455950;

__attribute__((section(".text.func_003391F8")))
void func_003391F8(SjMem3391F8 *sj, int id, Chunk3391F8 *ck)
{
    void (*cb)(void *obj, int ev);
    int n;

    if (sj == 0) {
        func_00338A48(&D_00455A10, &D_00455920);
        return;
    }
    if (sj->used == 0) {
        func_00338A48(&D_00455A20, &D_00455950);
        return;
    }
    if (ck->len > 0 && ck->data != 0) {
        if (id == 0)
            goto err;
        if (id == 1) {
            n = sj->free - ck->len;
            sj->free = n < 0 ? 0 : n;
            n = sj->data + ck->len;
            sj->data = sj->size < n ? sj->size : n;
            if (sj->free != ck->data - sj->base) {
            err:
                if (sj->cb != 0)
                    sj->cb(sj->cbobj, -3);
            }
        } else {
            cb = sj->cb;
            ck->len = 0;
            ck->data = 0;
            if (cb != 0)
                cb(sj->cbobj, -3);
        }
    }
}
