/* cygnus-2.96: Sofdec end-code check: latch the end flag and offset on an end code, finish the stream
 * on an effective end code, and say whether more data is needed. */
typedef struct {
    char pad0[0x3C];
    int ended;            /* 0x3C */
} SfdEndCtx;

typedef struct {
    char pad0[0x8];
    SfdEndCtx *ctx;       /* 0x8 */
    char padC[0x4];
    int arg;              /* 0x10 */
    char pad14[0xC];
    int ofs;              /* 0x20 */
} SfdEndSub;

typedef struct {
    char pad0[0x1F74];
    SfdEndSub sub;        /* 0x1F74 */
} SfdEndView;

extern int func_00368A28(unsigned char *buf);
extern int func_0034C7D0(SfdEndView *w, int arg);
extern int sfmps_IsEffectiveEndcode(SfdEndView *w, int code);
extern void func_0034F390(SfdEndView *w, int flag);
extern void func_0034F658(SfdEndView *w, int *out);

__attribute__((section(".text.func_0034F4C0")))
int func_0034F4C0(SfdEndView *w, unsigned char *buf, int len, int len2)
{
    SfdEndSub *s = &w->sub;
    SfdEndCtx *c = s->ctx;
    int arg = s->arg;
    int code;
    int r;

    if (len >= 4) {
        code = func_00368A28(buf);
        if (code == 0x80000) {
            if (s->ofs < 0)
                s->ofs = func_0034C7D0(w, arg) + 4;
            c->ended = 1;
        } else if (code != 0) {
            c->ended = 0;
        }
    } else {
        code = 0;
    }
    if (sfmps_IsEffectiveEndcode(w, code)) {
        func_0034F390(w, 1);
        return 0;
    }
    if (len2 < 4) {
        func_0034F658(w, &r);
        if (r != 0)
            return 0;
    }
    if (len >= 0x40)
        return 1;
    if (code != 0x10000 && code != 0x40000)
        return 1;
    func_0034F658(w, 0);
    return 0;
}
