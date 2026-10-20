/* sn-2.95.3-136: cMessDrawFont message width and height (0x2B1090..). */

#include "godhand/cMessDrawFontCode.h"

__attribute__((section(".text.func_002B1168")))
float func_002B1168(cMessDrawFont *self, int id, float *scale)
{
    unsigned short *text;
    float h, ch;

    h = 0.0f;
    text = cMessage_getMessageAddr(D_003C23A4, id);
    goto check;
    do {
        ch = (float)func_002A4B88(D_003C2380, *text) * (*scale * self->charH * self->zoomY);
        if (h < ch) {
            h = ch;
        }
next:
        text += cMessCommon_getCodeSize(*text);
check:
        if (!(*text >> 15)) {
            continue;
        }
        if ((*text & 0xFF00) != 0x8000) {
            goto next;
        }
        break;
    } while (1);
    if (self->flags & 1) {
        h += (self->unk34[1] + 12.0f) * self->zoomY;
    }
    return h;
}
