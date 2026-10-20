/* cygnus-2.96 matched TU. */

typedef struct {
    char pad[0x40];
    int x;
    int y;
} Pos;

typedef struct {
    char pad[0xA4];
    unsigned int mode;
    char pad2[0x160 - 0xA8];
    Pos *a;
    Pos *b;
} Obj;

typedef struct {
    char pad[0x38];
    int state;
} Ctx;

__attribute__((section(".text.func_00353EE0")))
void func_00353EE0(Ctx *ctx, Obj *obj, int *x, int *y) {
    if (ctx->state == 3) {
        switch (obj->mode) {
        case 2:
            *x = obj->a->x;
            *y = obj->a->y;
            return;
        case 3:
            *x = obj->a->x + obj->b->x;
            *y = obj->a->y + obj->b->y;
            return;
        case 1:
            break;
        }
    }
    *x = 0;
    *y = 0;
}
