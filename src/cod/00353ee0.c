/* cygnus-2.96 matched TU. */
#include "godhand/Sfd.h"

/* Write the movie's draw offset to *x, *y: the base position, or base plus
   relative position, while playing; 0, 0 otherwise. */
__attribute__((section(".text.func_00353EE0")))
void func_00353EE0(SfdPlayCtx *ctx, SfdDrawObj *obj, int *x, int *y) {
    if (ctx->state == SFD_PLAY_STATE_PLAYING) {
        switch (obj->mode) {
        case SFD_DRAW_MODE_BASE:
            *x = obj->base->x;
            *y = obj->base->y;
            return;
        case SFD_DRAW_MODE_BASE_REL:
            *x = obj->base->x + obj->rel->x;
            *y = obj->base->y + obj->rel->y;
            return;
        case SFD_DRAW_MODE_NONE:
            break;
        }
    }
    *x = 0;
    *y = 0;
}
