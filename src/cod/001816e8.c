/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"

extern void func_001B6FB8(void *self);
extern void cOmDoor_setObjCollision(void *self);
/* func_001BBF68 stays undeclared on purpose: an implicit int declaration keeps retail's jal slot store. */

/* A door object: the fields the constructor sets. */
typedef struct DoorObj {
    char unk000[0x548];
    short life;                         /* 0x548 */
    short lifeMax;                      /* 0x54A */
    char unk54C[0x6C];
    unsigned int flags;                 /* 0x5B8 */
    char unk5BC[0x54];
    float size[3];                      /* 0x610 */
    char unk61C[8];
    unsigned char hasBody;              /* 0x624 */
    char unk625[3];
    void *body;                         /* 0x628 */
    char unk62C[0x24];
    char bodyRec[1];                    /* 0x650 */
} DoorObj;

#define DOOR_FLAG_BOX  0x2

/* Set up a door object: 1 life (0x548, 0x54A), a 1.66 by 4.47 by 0.2 box kept
 * at 0x610, its collision object, a body at 0x650 and flag bit 1 in 0x5B8.
 * Returns 1. */
__attribute__((section(".text.DoorObj_construct2")))
int DoorObj_construct2(DoorObj *self) {
    float f[8];
    float *t;
    int hp;
    float one, ca, cb, cc, cd;
    func_001B6FB8(self);
    hp = 1;
    one = 1.0f;
    ca = 1.66f;
    cb = 4.47f;
    cc = 0.2f;
    cd = -0.83f;
    t = &f[4];
    f[0] = ca;
    f[1] = cb;
    f[2] = cc;
    f[4] = cd;
    f[3] = one;
    t[3] = one;
    f[5] = 0.0f;
    f[6] = 0.0f;
    self->life = hp;
    self->lifeMax = hp;
    cVec_copy3((cVec *)self->size, (cVec *)f);
    cOmDoor_setObjCollision(self);
    self->hasBody = hp;
    self->body = self->bodyRec;
    func_001BBF68(self);
    self->flags |= DOOR_FLAG_BOX;
    return 1;
}
