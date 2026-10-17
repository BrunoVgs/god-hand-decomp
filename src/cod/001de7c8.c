/* sn-2.95.3-136 matched TU. */

#include "godhand/CustomIDWork.h"
#include "godhand/Slot2.h"
#include "godhand/cNode.h"

extern void CustomIDWork_SetOffsetPosX(CustomIDWork *work, int x);
extern void CustomIDWork_SetMoveOffsetPosX(CustomIDWork *work, int from, int to, int frames);
extern void displayScrollLayer(int layer, int on);
extern float *CallThenReturnPlusB0_002B6420_2B61B0(cNode *node);
extern float *func_002B6328(cNode *node);
extern void MtxMultiply(float *dst, float *a, float *b);
extern void MtxCopy(float *dst, float *src);
extern void *Gp_draw_poly4(void *v, int color, int count, void *ctx, int a5, int a6);

#define SLIDE_OFFSET_X  (-0xDC)         /* x offset of the panel when hidden */
#define SLIDE_FRAMES    10

#define PANEL_HIDE      0               /* any unknown mode hides too */
#define PANEL_SHOW      1
#define PANEL_SLIDE_OUT 2
#define PANEL_SLIDE_IN  3

typedef struct Panel1DE7C8 {
    char unk000[0x994];
    CustomIDWork panel;                 /* 0x994 */
} Panel1DE7C8;

/* Moves the panel by mode: PANEL_SHOW puts it in place, PANEL_SLIDE_OUT and
 * PANEL_SLIDE_IN slide it, anything else hides it at once. */
__attribute__((section(".text.func_001DE7C8")))
void func_001DE7C8(Panel1DE7C8 *self, unsigned char mode)
{
    switch (mode) {
    case PANEL_HIDE:
    default:
        CustomIDWork_SetOffsetPosX(&self->panel, SLIDE_OFFSET_X);
        break;
    case PANEL_SHOW:
        CustomIDWork_SetOffsetPosX(&self->panel, 0);
        break;
    case PANEL_SLIDE_OUT:
        CustomIDWork_SetMoveOffsetPosX(&self->panel, SLIDE_OFFSET_X, 0, SLIDE_FRAMES);
        break;
    case PANEL_SLIDE_IN:
        CustomIDWork_SetMoveOffsetPosX(&self->panel, 0, SLIDE_OFFSET_X, SLIDE_FRAMES);
        break;
    }
}

#define MARK_LIT        0x8000          /* markFlag: the mark blinks */
#define MARK_ON         0x4000          /* markFlag: shown in this blink phase */
#define MARK_COUNT_MASK 0x3FFF          /* frames spent in the phase */
#define MARK_PHASE_LEN  8
#define SLOT2_LINE_LAYER_B(s)  (*(int *)(s)->unk3CC)    /* second line layer, 0x3CC */

/* Per frame: counts a lit mark's phase and, after MARK_PHASE_LEN frames,
 * flips it between on and off and shows or hides both line layers. */
__attribute__((section(".text.func_001E6BE8")))
void func_001E6BE8(Slot2 *self)
{
    unsigned int flag = self->markFlag[0];
    if (flag & MARK_LIT) {
        flag++;
        self->markFlag[0] = flag;
        if ((flag & MARK_COUNT_MASK) >= MARK_PHASE_LEN) {
            unsigned int next = (unsigned short)((~flag & MARK_ON) | MARK_LIT);
            self->markFlag[0] = next;
            if (next & MARK_ON) {
                displayScrollLayer(self->lineLayer, 1);
                displayScrollLayer(SLOT2_LINE_LAYER_B(self), 1);
            } else {
                displayScrollLayer(self->lineLayer, 0);
                displayScrollLayer(SLOT2_LINE_LAYER_B(self), 0);
            }
        }
    }
}

#define NODE_FLAG_WORLD_VALID  1        /* unk90: the world matrix is up to date */

/* Builds the node's world matrix (matWorld) unless it is already valid:
 * parent matrix times the local one, or just the local one for a root. */
__attribute__((section(".text.func_002B6420")))
void func_002B6420(cNode *self)
{
    if (func_002B6510(self) == 0) {
        cNode *parent = func_002B5E50(self);
        if (parent != 0) {
            float *parentMtx = CallThenReturnPlusB0_002B6420_2B61B0(parent);
            MtxMultiply((float *)self->matWorld, parentMtx, func_002B6328(self));
        } else {
            MtxCopy((float *)self->matWorld, func_002B6328(self));
        }
        self->unk90 |= NODE_FLAG_WORLD_VALID;
    }
}

#define NODE_FLAG_ACTIVE  1             /* unk90 bit 0: the node is being walked */

/* Depth first walk: for an active node, visits every child (recursing into
 * func_002B6370) and then clears the active flag. unk90 is signed in cNode.h
 * and retail masks it as unsigned, hence the cast. */
__attribute__((section(".text.func_002B6370")))
void func_002B6370(cNode *self)
{
    if (func_002B6510(self) != 0) {
        int i;
        int n = func_002B5E58(self);
        for (i = 0; i < n; i++) {
            func_002B6370(func_002B5E90(self, i));
        }
        self->unk90 = (unsigned int)self->unk90 & ~NODE_FLAG_ACTIVE;
    }
}

#define SCREEN_W  512.0f
#define SCREEN_H  448.0f
#define POLY_CTX_MODE   0x20
#define POLY_CTX_REG    0x32001         /* register word at ctx + 0x30 */

typedef struct Vtx {
    float x, y, z, w;
} Vtx;

/* Draws one grey quad over the whole 512x448 screen. */
__attribute__((section(".text.func_002C7850")))
void func_002C7850(void *unused, int arg5, int arg6)
{
    char ctx[0x50];
    Vtx v[4];
    *(int *)ctx = POLY_CTX_MODE;
    *(long *)(ctx + 0x30) = POLY_CTX_REG;
    v[0].x = 0.0f;
    v[0].y = 0.0f;
    v[0].z = 0.0f;
    v[0].w = 1.0f;
    v[1].x = SCREEN_W;
    v[1].y = 0.0f;
    v[1].z = 0.0f;
    v[1].w = 1.0f;
    v[2].x = 0.0f;
    v[2].y = SCREEN_H;
    v[2].z = 0.0f;
    v[2].w = 1.0f;
    v[3].x = SCREEN_W;
    v[3].y = SCREEN_H;
    v[3].z = 0.0f;
    v[3].w = 1.0f;
    Gp_draw_poly4(v, 0x80808080, 1, ctx, arg5, arg6);
}
