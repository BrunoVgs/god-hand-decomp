/* sn-2.95.3-136 matched TU. */

#include "godhand/vu0.h"
#include "godhand/cOmBase.h"

extern char *func_001F0498(void *owner, int obj, cVec *pos, float angle);   /* create one piece */

#define PIECE_KIND  0x3EC

typedef struct Obj1F0BF8 {
    char unk000[0xC64];
    char *piece[3];                     /* 0xC64 the three pieces */
} Obj1F0BF8;

/* Create three pieces at fixed offsets from the owner: (2.9, 0, 5.4), (3.0, 0, -4.55) and (-5.4, 0, -1.0), all with angle 0. */
__attribute__((section(".text.Obj_spawnThreePieces")))
void Obj_spawnThreePieces(Obj1F0BF8 *self)
{
    cVec v;
    float zero;
    v.y = 0.0f;
    zero = v.y;                       /* the angle is the y just stored, read back from the stack */
    v.x = 2.9f;
    v.z = 5.4f;
    v.w = 1.0f;
    self->piece[0] = func_001F0498(self, PIECE_KIND, &v, zero);
    v.x = 3.0f;
    v.y = zero;
    v.z = -4.55f;
    v.w = 1.0f;
    self->piece[1] = func_001F0498(self, PIECE_KIND, &v, zero);
    v.x = -5.4f;
    v.y = zero;
    v.z = -1.0f;
    v.w = 1.0f;
    self->piece[2] = func_001F0498(self, PIECE_KIND, &v, zero);
}
