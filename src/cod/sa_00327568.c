/* cygnus-2.96: func_00327568, skips the bytes all channel stream joints have available (rounded to an
 * even count) and subtracts the per-channel amount from the pending total. */
typedef struct SjCk327568 {
    char *data;
    int len;
} SjCk327568;

typedef struct Sj327568 Sj327568;

typedef struct SjIf327568 {
    void *fn[6];
    void (*GetChunk)(Sj327568 *sj, int id, int nbyte, SjCk327568 *ck);    /* 0x18 */
    void (*UngetChunk)(Sj327568 *sj, int id, SjCk327568 *ck);             /* 0x1C */
    void (*PutChunk)(Sj327568 *sj, int id, SjCk327568 *ck);               /* 0x20 */
} SjIf327568;

struct Sj327568 {
    SjIf327568 *vtbl;
};

typedef struct Dec327568 {
    char pad0[2];
    signed char nch;                    /* 0x02 */
    char pad3[9];
    Sj327568 *sj[(0xA4 - 0xC) / 4];     /* 0x0C */
    int pending;                        /* 0xA4 */
} Dec327568;

__attribute__((section(".text.func_00327568")))
void func_00327568(Dec327568 *dec)
{
    SjCk327568 ck;
    int i;
    int n;
    int half;

    n = dec->pending * 2;
    for (i = 0; i < dec->nch; i++) {
        dec->sj[i]->vtbl->GetChunk(dec->sj[i], 1, 0x7FFFFFFF, &ck);
        n = (n < ck.len) ? n : ck.len;
        dec->sj[i]->vtbl->UngetChunk(dec->sj[i], 1, &ck);
    }
    half = n / 2;
    n = half * 2;
    if (n > 0) {
        for (i = 0; i < dec->nch; i++) {
            dec->sj[i]->vtbl->GetChunk(dec->sj[i], 1, n, &ck);
            dec->sj[i]->vtbl->PutChunk(dec->sj[i], 0, &ck);
        }
        dec->pending -= half;
    }
}
