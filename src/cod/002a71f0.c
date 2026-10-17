/* sn-2.95.3-136 matched TU. */

/* g++ 2.x method table entry: this adjustment, vtable index, function. */
typedef struct HandlerVt {
    char unk00[0x30];
    short delta;                        /* 0x30 */
    short index;                        /* 0x32 */
    void (*pfn)(void *self, void *rec); /* 0x34 */
} HandlerVt;

#define REC_FLAG_USED   0x001
#define REC_FLAG_SKIP   0x200

/* A pool of equal-size records, each starting with a flag word. */
typedef struct RecPool {
    char *rec;                          /* 0x00 first record, 0 while unloaded */
    unsigned int num;                   /* 0x04 */
    int recSize;                        /* 0x08 */
    char unk0C[0xC];
    HandlerVt *vt;                      /* 0x18 */
} RecPool;

/* Hand every used, not skipped record to the pool's handler. */
__attribute__((section(".text.RecPool_dispatchUsed")))
void RecPool_dispatchUsed(RecPool *self)
{
    unsigned int i;
    char *rec;

    if (self->rec != 0) {
        for (i = 0; i < self->num; i++) {
            rec = self->rec + self->recSize * i;
            if (((*(unsigned int *)rec & (REC_FLAG_USED | REC_FLAG_SKIP)) ^ REC_FLAG_USED) == 0)
                self->vt->pfn((char *)self + self->vt->delta, rec);
        }
    }
}
