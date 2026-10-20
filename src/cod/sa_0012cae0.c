#include "godhand/cGameObj.h"

typedef struct Sys12CAE0 {
    unsigned int flags;
    char pad4[0x21];
    unsigned char stage;
} Sys12CAE0;

typedef struct Obj12CAE0 {
    cGameObj base;
    char unk5AC[0x15D0 - 0x5AC];
    float hitWait;
    char unk15D4[0xC];
    char hit[0x10];
} Obj12CAE0;

extern Sys12CAE0 D_00747A2C;
extern char D_005FEA60[];
extern int FindNodeByHit_2C2490(void *mgr, void *pos, void *out);
extern int SetEffect(int a0, int a1, void *a2, void *a3, int t0, unsigned int t1);

__attribute__((section(".text.func_0012CAE0")))
int func_0012CAE0(Obj12CAE0 *o)
{
    int r;
    int one;
    unsigned long f;

    if (o->hitWait > 0.0f)
        return 0;
    if (o->base.hitFlash > 0.0f)
        return 0;
    f = D_00747A2C.flags;
    f = (f >> 3) & 1;
    if (f)
        return 0;
    r = FindNodeByHit_2C2490(D_005FEA60, o->base.pos, o->hit);
    if (r == 1) {
        o->hitWait = 90.0f;
        if (D_00747A2C.stage == 5)
            SetEffect(0, 0x4B, o, 0, -1, 0xFFFFFFFF);
        if (o->base.hp >= 11) {
            o->base.hp -= 25;
            if (o->base.hp <= 0)
                o->base.hp = r;
        } else {
            o->base.hp = 0;
        }
        one = 1;
        o->base.mode = one;
        o->base.phase = 7;
        o->base.step = 0;
        o->base.stepArg = 0;
        return one;
    }
    return 0;
}
