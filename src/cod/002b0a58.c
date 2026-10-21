/* cMessDrawFont code height (func_002B0A58, the height pass of the 001599b0.c measure loop). Control codes 0xA8xx (space),
 * 0x93xx and 0x94xx (inline icons) have their own sizes; a plain code takes the font metric, plus
 * the ruby band when ruby text is drawn. func_002B0BE0 is the same body on the font's other metric. */
#include "godhand/cMessDrawFontCode.h"

extern int Obj0000_Get_D_003C23A4_By_Short_A1p2_2B1270(cMessDrawFont *self, unsigned short *text);
extern int GetField_BEE_2B1290(cMessDrawFont *self);
extern float func_002B0F20(cMessDrawFont *self, int id, float *scale);
extern float func_002B1168(cMessDrawFont *self, int id, float *scale);
extern int func_002B12A0(unsigned short *text);
extern float func_002B12D8(void);

__attribute__((section(".text.func_002B0A58")))
float func_002B0A58(cMessDrawFont *self, unsigned short *text, float *scale)
{
    float w;

    if (*text >> 15) {
        switch (*text & 0xFF00) {
        case 0xA800:
            w = *scale * self->charH * self->zoomY * 26.0f;
            break;
        case 0x9300:
            w = func_002B0F20(self, Obj0000_Get_D_003C23A4_By_Short_A1p2_2B1270(self, text), scale);
            break;
        case 0x9400:
            w = func_002B1168(self, GetField_BEE_2B1290(self), scale);
            break;
        default:
            w = 0.0f;
            break;
        }
    } else if (func_002B12A0(text)) {
        w = func_002B12D8() * (*scale * self->charH * self->zoomY);
        if (self->flags & 1)
            w += (self->unk34[1] + 12.0f) * self->zoomY;
    } else {
        w = (float)func_002A4B88(D_003C2380, *text) * (*scale * self->charH * self->zoomY);
        if (self->flags & 1)
            w += (self->unk34[1] + 12.0f) * self->zoomY;
    }
    return w;
}

__attribute__((section(".text.func_002B0BE0")))
float func_002B0BE0(cMessDrawFont *self, unsigned short *text, float *scale)
{
    float w;

    if (*text >> 15) {
        switch (*text & 0xFF00) {
        case 0xA800:
            w = *scale * self->charH * self->zoomY * 26.0f;
            break;
        case 0x9300:
            w = func_002B0F20(self, Obj0000_Get_D_003C23A4_By_Short_A1p2_2B1270(self, text), scale);
            break;
        case 0x9400:
            w = func_002B1168(self, GetField_BEE_2B1290(self), scale);
            break;
        default:
            w = 0.0f;
            break;
        }
    } else if (func_002B12A0(text)) {
        w = func_002B12D8() * (*scale * self->charH * self->zoomY);
        if (self->flags & 1)
            w += (self->unk34[1] + 12.0f) * self->zoomY;
    } else {
        w = (float)func_002A4BA0(D_003C2380, *text) * (*scale * self->charH * self->zoomY);
        if (self->flags & 1)
            w += (self->unk34[1] + 12.0f) * self->zoomY;
    }
    return w;
}
