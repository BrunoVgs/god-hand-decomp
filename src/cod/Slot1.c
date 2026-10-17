/* The constructor is a function named Slot1, as in the retail symbol table, so
 * the record type gets another name for this file. */
#define Slot1 Slot1Obj
#include "godhand/Slot1.h"
#undef Slot1

extern void func_003A52F0(void *dst, int val, int len);
extern void InitStructSubfieldsAndFloatB(void *reel);
extern void InitStructZeroedFields_1E7960(void *panel);
extern void *func_001E7118(void *ui);   /* returns a pointer (int return also matches) */

#define SLOT1_REEL_NUM     3
#define SLOT1_REEL_SIZE    0x108
#define SLOT1_HEAD_SIZE    0x54         /* bytes the constructor clears first */
#define SLOT1_PANEL_OFS    0x370
#define SLOT1_UI_OFS       0x4D0

/* Fields past what Slot1.h names, as raw offsets (see Slot1_fields.h). */
#define SLOT1_AT(s, ofs, type)  (*(type *)((char *)(s) + (ofs)))

/* Constructor: clears the head, builds the three reels, the panel and the ui,
 * and resets the pay state. Returns the machine. */
__attribute__((section(".text.Slot1")))
Slot1Obj *Slot1(Slot1Obj *self)
{
    char *reel;
    int i;
    func_003A52F0(self, 0, SLOT1_HEAD_SIZE);
    *(int *)((char *)self + SLOT1_HEAD_SIZE) = 0;
    reel = self->reel;
    for (i = SLOT1_REEL_NUM - 1; i != -1; i--) {
        InitStructSubfieldsAndFloatB(reel);
        reel += SLOT1_REEL_SIZE;
    }
    InitStructZeroedFields_1E7960((char *)self + SLOT1_PANEL_OFS);
    func_001E7118((char *)self + SLOT1_UI_OFS);
    SLOT1_AT(self, 0x48C, unsigned short) = 0xFFFF;
    self->payMode = SLOT1_PAYMODE_ON;
    SLOT1_AT(self, 0x4B0, int) = 0;
    SLOT1_AT(self, 0x4B4, int) = 0;
    SLOT1_AT(self, 0x4B8, int) = 0;
    SLOT1_AT(self, 0x4BC, int) = 0;
    SLOT1_AT(self, 0x498, int) = 0;
    SLOT1_AT(self, 0x4C2, short) = 0;
    SLOT1_AT(self, 0xB50, short) = 0;
    SLOT1_AT(self, 0xB52, short) = 0;
    return self;
}
