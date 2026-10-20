/* include/godhand/cMessDrawFontCode.h - per-code glyph height of cMessDrawFont.
 *
 * func_002B0A58 and func_002B0BE0 are one body on the font's two metrics
 * (func_002A4B88 and func_002A4BA0). cMessDrawFont.unk34[1] (0x38) is the
 * ruby band height they add when flags & 1. Kept apart from cMessDrawFont.h
 * because older callers declare func_002B0A58 with a different third
 * parameter type.
 */
#ifndef GODHAND_CMESSDRAWFONTCODE_H
#define GODHAND_CMESSDRAWFONTCODE_H

#include "godhand/cMessDrawFont.h"

extern float func_002B0A58(cMessDrawFont *self, unsigned short *text, float *scale);
extern float func_002B0BE0(cMessDrawFont *self, unsigned short *text, float *scale);
extern int func_002A4B88(int font, unsigned short code);
extern int func_002A4BA0(int font, unsigned short code);
extern int D_003C2380;          /* the font the metrics read */
extern int D_003C23A4;          /* the message bank the metrics read */
extern unsigned short *cMessage_getMessageAddr(int mess, unsigned short id);
extern int cMessCommon_getCodeSize(unsigned short code);
extern int func_002A4B20(int font, unsigned short code);

#endif
