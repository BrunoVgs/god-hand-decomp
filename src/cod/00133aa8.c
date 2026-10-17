/* sn-2.95.3-136 matched TU. */

#include "godhand/Slot2.h"
#include "godhand/cCollisionSolid.h"
#include "godhand/cCoreSave.h"

extern void ModeObj_pollInputBits(void *self);
extern void func_00164238(void *self);
extern void func_001643F8(void *self);
extern void displayScrollLayer(int layer, int on);
extern void sceVu0ApplyMatrix(void *dst, void *mtx, void *vec);
extern int irand(void);

/* Phases of the screen: 0 polls the input, 1 and 2..3 run their own updates. */
#define SCREEN_PHASE_POLL   0
#define SCREEN_PHASE_RUN    1
#define SCREEN_PHASE_RUN2   2           /* 2 and 3 */
#define SCREEN_PHASE_RUN3   3

typedef struct Screen164140 {
    char unk00[0x64];
    unsigned char phase;                /* 0x64 */
} Screen164140;

/* Runs the update for the screen's current phase. */
__attribute__((section(".text.func_00164140")))
void func_00164140(Screen164140 *self)
{
    switch (self->phase) {
    case SCREEN_PHASE_POLL:
        ModeObj_pollInputBits(self);
        break;
    case SCREEN_PHASE_RUN:
        func_00164238(self);
        break;
    case SCREEN_PHASE_RUN2:
    case SCREEN_PHASE_RUN3:
        func_001643F8(self);
        break;
    }
}

#define MARK_LIT    0x8000              /* markFlag: start mark lit */
#define MARK_ON     0x4000              /* markFlag: line marks on */
#define SLOT2_LINE_LAYER_B(s)  (*(int *)(s)->unk3CC)    /* second line layer, 0x3CC */

/* Sets the first mark: lit when `lit`; when `on` also flags the line marks and
 * shows both line layers, otherwise hides them. */
__attribute__((section(".text.func_001E6B70")))
void func_001E6B70(Slot2 *self, int on, int lit)
{
    self->markFlag[0] = 0;
    if (lit) {
        self->markFlag[0] = MARK_LIT;
    }
    if (on) {
        self->markFlag[0] |= MARK_ON;
        displayScrollLayer(self->lineLayer, 1);
        displayScrollLayer(SLOT2_LINE_LAYER_B(self), 1);
    } else {
        displayScrollLayer(self->lineLayer, 0);
        displayScrollLayer(SLOT2_LINE_LAYER_B(self), 0);
    }
}

extern unsigned int D_00747A80;         /* the global input/event lock bits */

typedef struct Obj2BF708 {
    char unk00[0x70];
    unsigned int savedLock;             /* 0x70 D_00747A80 as it was before */
} Obj2BF708;

/* Retail reloads D_00747A80 after this store, so the store must carry the
 * plain unsigned int alias set; a struct field access would not. */
#define SAVED_LOCK(o)  (*(unsigned int *)((char *)(o) + 0x70))

/* Remembers the lock bits in the object, then sets bits 20 to 31. */
__attribute__((section(".text.func_002BF708")))
void func_002BF708(Obj2BF708 *self)
{
    SAVED_LOCK(self) = D_00747A80;
    D_00747A80 |= 0x80000000;
    D_00747A80 |= 0x40000000;
    D_00747A80 |= 0x20000000;
    D_00747A80 |= 0x10000000;
    D_00747A80 |= 0x8000000;
    D_00747A80 |= 0x4000000;
    D_00747A80 |= 0x2000000;
    D_00747A80 |= 0x1000000;
    D_00747A80 |= 0x800000;
    D_00747A80 |= 0x400000;
    D_00747A80 |= 0x200000;
    D_00747A80 |= 0x100000;
}

/* Moves the sphere centre into world space, then rebuilds the box around it:
 * unk10 gets the corner at centre - radius, unk20 the corner at centre + radius.
 * Clears flag bit 1 (the box is up to date). */
__attribute__((section(".text.func_00133AA8")))
void func_00133AA8(cCollisionSolidObj *self)
{
    float r;
    sceVu0ApplyMatrix(&self->unk60, self->owner, &self->center);
    r = self->radius;
    self->unk10.x = self->unk60.x - r;
    self->unk10.y = self->unk60.y - r;
    self->unk10.z = self->unk60.z - r;
    self->unk20.x = self->unk60.x + r;
    self->unk20.y = self->unk60.y + r;
    self->unk20.z = self->unk60.z + r;
    /* signed mask: retail builds ~2 with one addiu */
    self->flags = (int)self->flags & ~2;
}

extern int D_0061A990;                  /* a counter that changes every frame */


/* A pseudo-random number in lo..hi, mixed from the frame counter, the gold
 * and a random draw. */
__attribute__((section(".text.func_001DCE68")))
int func_001DCE68(void *self, int lo, int hi)
{
    unsigned int seed = D_0061A990;
    int gold = cCoreSave_getGold(&D_00569B70);
    int r = irand();
    int base = lo - 1;
    hi -= base;
    seed += gold / 100;
    seed += r;
    return seed % hi + lo;
}
