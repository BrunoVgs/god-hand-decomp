/* include/godhand/cFont.h - cFont, the font texture and text sprite pool.
 *
 * The one instance is D_003C2380. The record is large (a texture table and
 * two sprite buffers); the part we know starts at 0x2A050, the "state"
 * block: a bump allocator (cur, end) for sprite memory plus the draw
 * settings of the text being laid out (colour, layer, scale).
 *
 * Method names are the game's own, from the symbol table in the retail ELF.
 * Field names are ours, taken from the methods that read and write them.
 * Offsets are exact: every body that uses this header builds byte-identical
 * to retail. A field we can't name yet stays as unkNNN padding.
 */
#ifndef GODHAND_CFONT_H
#define GODHAND_CFONT_H

#define CFONT_STATE_OFFSET  0x2A050     /* start of cFontState inside cFont */

typedef struct cFontState {
    int kind;                           /* 0x00 (0x2A050) */
    char *cur;                          /* 0x04 next free byte of sprite memory */
    char *end;                          /* 0x08 end of sprite memory */
    int mode;                           /* 0x0C */
    int phase;                          /* 0x10 */
    int phaseArg;                       /* 0x14 */
    char unk18[0xC];
    int colour;                         /* 0x24 packed RGBA, 0x80808080 is neutral */
    short layer;                        /* 0x28 */
    char unk2A[2];
    float scaleX;                       /* 0x2C */
    float scaleY;                       /* 0x30 */
    float unk34;                        /* 0x34 */
    float unk38;                        /* 0x38 */
} cFontState;

typedef struct cFont {
    char unk000[CFONT_STATE_OFFSET];
    cFontState state;                   /* 0x2A050 */
} cFont;

typedef char cFont_state_check[(sizeof(cFont) == CFONT_STATE_OFFSET + 0x3C) ? 1 : -1];

#endif
