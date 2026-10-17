/* sn-2.95.3-136 matched TU. */

#include "godhand/cMessDrawFont.h"

extern void *cMessage_getMessageAddr(void *a, int b);
extern unsigned int cMessCommon_getCodeSize(unsigned int code);
extern void *D_003C23A4;
extern void *D_003C2380;
extern int func_002B12A0(unsigned short *text);
extern float func_002B12D8(void);
extern int Obj0000_Get_D_003C23A4_By_Short_A1p2_2B1270(cMessDrawFont *self, unsigned short *text);
extern unsigned short GetField_BEE_2B1290(cMessDrawFont *self);
extern float func_002B0D68(cMessDrawFont *self, int value, float *arg);
extern float func_002B1090(cMessDrawFont *self, unsigned short msgNo, float *arg);

#define MSGCODE_END_MASK   0xFF00
#define MSGCODE_END_GROUP  0x8000

/* Width of a message line: sum each plain code's glyph advance, scaled by arg[0], charW and zoomX plus the spacing at unk2C[0] scaled by zoomX, until a code of the 0x8000 group; the last spacing is taken back off. */
__attribute__((section(".text.func_002B1090")))
float func_002B1090(cMessDrawFont *self, unsigned short msgNo, float *arg)
{
    unsigned short *p = cMessage_getMessageAddr(D_003C23A4, msgNo);
    float acc = 0.0f;
    goto test;
    do { } while (0);
plain:
    {
        float adv = (float)func_002A4B20(D_003C2380, *p);
        acc += adv * (*arg * self->charW * self->zoomX) + self->unk2C[0] * self->zoomX;
    }
skip:
    p += cMessCommon_getCodeSize(*p);
test:
    if ((*p >> 15) == 0) {
        goto plain;
    }
    if ((*p & MSGCODE_END_MASK) != MSGCODE_END_GROUP) {
        goto skip;
    }
    return acc - self->unk2C[0] * self->zoomX;
}

#define MSGCODE_GROUP_MASK  0xFF00
#define MSGCODE_NUMBER      0x9300      /* print a number */
#define MSGCODE_MESSAGE     0x9400      /* print another message */
#define MSGCODE_SPACE       0xA800      /* a gap of ten cells */
#define MSGCODE_SPACE_CELLS 40.0f

/* Width of one message code: a message or number code measures what it would print, a space is a fixed gap, any other control code is 0; a plain code is its glyph advance (the fixed width for the codes func_002B12A0 marks) times the scale in *arg, charW and zoomX. */
__attribute__((section(".text.func_002B0908")))
float func_002B0908(cMessDrawFont *self, unsigned short *text, float *arg)
{
    unsigned int code = *text;
    if ((code >> 15) != 0) {
        switch ((int)(code & MSGCODE_GROUP_MASK)) {
        case MSGCODE_SPACE:
            return *arg * self->charW * self->zoomX * MSGCODE_SPACE_CELLS;
        case MSGCODE_NUMBER:
            return func_002B0D68(self, Obj0000_Get_D_003C23A4_By_Short_A1p2_2B1270(self, text), arg);
        case MSGCODE_MESSAGE:
            return func_002B1090(self, GetField_BEE_2B1290(self), arg);
        default:
            return 0.0f;
        }
    }
    if (func_002B12A0(text) != 0) {
        return func_002B12D8() * (*arg * self->charW * self->zoomX);
    }
    return (float)func_002A4B20(D_003C2380, *text) * (*arg * self->charW * self->zoomX);
}
