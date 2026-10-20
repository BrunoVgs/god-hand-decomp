typedef struct SfdTcSub {
    char pad00[0x70];
    int *cur;
} SfdTcSub;

typedef struct SfdTcCtx {
    char pad0000[0x58];
    int mode;
    char pad005C[0x1FC0 - 0x5C];
    SfdTcSub *sub;
} SfdTcCtx;

extern int *func_00355450(SfdTcCtx *ctx, int key);
extern int *func_00355490(SfdTcCtx *ctx, int *ent);
extern int *func_00355258(SfdTcCtx *ctx, int id);
extern int *func_00355408(SfdTcCtx *ctx, int id);
extern void func_00355670(int *ent);
extern int func_0034DD70(SfdTcCtx *ctx, int err);

__attribute__((section(".text.func_00355130")))
int func_00355130(SfdTcCtx *ctx, int id, int key)
{
    SfdTcSub *sub = ctx->sub;
    int *ent;
    int *st;

    if (ctx->mode == 2) {
        ent = func_00355450(ctx, key);
        if (ent == 0) {
            return func_0034DD70(ctx, 0xFF000F1F);
        }
        st = func_00355490(ctx, ent);
    } else {
        st = func_00355258(ctx, id);
        if (*st != 1) {
            return func_0034DD70(ctx, 0xFF000F0E);
        }
        ent = func_00355408(ctx, id);
        if (sub->cur != ent) {
            return func_0034DD70(ctx, 0xFF000F0F);
        }
    }
    *st = 0;
    func_00355670(ent);
    return 0;
}
