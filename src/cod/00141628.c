/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"

extern void func_001B6FB8(void *self);
extern void cOmDoor_setObjCollision(void *self);
extern void ClearField90_13E400(void *);
extern void ResetBlendFields_13C930(void *);
extern void ResetAnimSlotArray_13F510(void *);
extern void func_0013E908(void *);
extern void ClearActiveSlot_147188(void *);
extern void cCockPlBar_initData(void *);

/* Set up a door object: 1 life (0x548, 0x54A), a 2.5 by 3.7 by 0.2 box kept
 * at 0x610, its collision object, a body at 0x650 and flag bit 1 in 0x5B8.
 * Returns 1. */






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

__attribute__((section(".text.func_001A8200")))
int func_001A8200(DoorObj *self) {
    float f[8];
    float *t;
    int hp;
    float one, ca, cb, cc, cd;
    func_001B6FB8(self);
    hp = 1;
    one = 1.0f;
    ca = 2.5f;
    cb = 3.7f;
    cc = 0.2f;
    cd = -1.25f;
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

/* Reset the sub-records of the player work area (arg) in a fixed order. */
#define WORK_FIELD90_OFFSET    0x1910   /* cleared by ClearField90_13E400 */
#define WORK_BLEND_OFFSET      0x1DC0   /* blend fields */
#define WORK_ANIM_SLOTS_OFFSET 0x1E90   /* animation slot array */
#define WORK_UNK2220_OFFSET    0x2220
#define WORK_ACTIVE_OFFSET     0x1A20   /* active slot record */
#define WORK_COCKBAR_OFFSET    0x460    /* cockpit bar data */








__attribute__((section(".text.func_00141628")))
void func_00141628(char *work) {
    ClearField90_13E400(work + WORK_FIELD90_OFFSET);
    ResetBlendFields_13C930(work + WORK_BLEND_OFFSET);
    ResetAnimSlotArray_13F510(work + WORK_ANIM_SLOTS_OFFSET);
    func_0013E908(work + WORK_UNK2220_OFFSET);
    ClearActiveSlot_147188(work + WORK_ACTIVE_OFFSET);
    cCockPlBar_initData(work + WORK_COCKBAR_OFFSET);
}
