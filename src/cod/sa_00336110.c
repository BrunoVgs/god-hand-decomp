/* cygnus-2.96: func_00336110, advances a 16-entry ring of queued requests; when the ring empties it
 * finishes the stream, and in mode 1 forwards the entry that was current. */
typedef struct Req336110 {
    int unk0;
    int a;      /* 0x04 */
    int unk8;
    int b;      /* 0x0C */
    int c;      /* 0x10 */
    int d;      /* 0x14 */
    char unk18[8];
} Req336110;

typedef struct Ring336110 {
    char unk0;
    char done;          /* 0x01 */
    char unk2;
    signed char mode;   /* 0x03 */
    char unk4[0x1C];
    int idx;            /* 0x20 */
    int count;          /* 0x24 */
    int active;         /* 0x28 */
    char unk2C[0xC];
    Req336110 req[16];  /* 0x38 */
} Ring336110;

extern void func_00335C30();
extern void func_00335638(Ring336110 *r, int a, int b, int c, int d);

__attribute__((section(".text.func_00336110")))
void func_00336110(Ring336110 *r)
{
    int a = 0, c = 0, d = 0, b = 0;

    if (r->active == 0)
        return;
    if (r->mode == 1) {
        Req336110 *q = &r->req[r->idx];
        c = q->c;
        a = q->a;
        b = q->b;
        d = q->d;
    }
    r->idx = (r->idx + 1) % 16;
    if (--r->count <= 0) {
        func_00335C30();
        r->done = 1;
    }
    if (r->mode == 1)
        func_00335638(r, a, b, c, d);
}
