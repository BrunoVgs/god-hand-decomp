/* sn-2.95.3-136 matched TU. */
#include "godhand/cOmBase.h"
#include "godhand/vu0.h"

/* vu0.h additions */
/* Store a VU0 quadword directly to a memory operand. */
#define VU0_SQC2_AT(reg, var) \
    __asm__ __volatile__(".set push\n.set noreorder\nsqc2 $vf" #reg ", %0\n.set pop\n" : : "m"(var) : "memory")

extern char D_005864F0[];
extern float cEmManage_GetSpeedRate(void *a0);
extern int ChkLine(cVec *from, cVec *to, cVec *hit, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12);
extern void SetEffectPos(int a0, int a1, int a2, void *a3, int a4, float a5);
extern void cOmWeapon_SetBreak(void *weapon);

typedef struct FallingWeapon {
    cOmBase base;
    char pad5E0[0x50];
    float gravity;
    char pad634[0x2C];
    float lifetime;
    char pad664[0x10];
    float velocity;
} FallingWeapon;

/* Advance a falling weapon and break it on impact or timeout. */
__attribute__((section(".text.func_001CD800")))
void func_001CD800(FallingWeapon *weapon)
{
    cVec to __attribute__((aligned(16)));
    cVec from __attribute__((aligned(16)));
    cVec hit __attribute__((aligned(16)));
    float speed = cEmManage_GetSpeedRate(D_005864F0);
    float remaining;
    VU0_SQC2_VF0_AT(to);
    VU0_LQC2(4, weapon->base.pos, 0);
    VU0_SQC2_AT(4, from);
    VU0_SQC2_VF0_AT(hit);
    switch (weapon->base.step) {
    case 0:
        weapon->gravity = 0.065f;
        weapon->lifetime = 300.0f;
        weapon->velocity = -weapon->gravity;
        weapon->base.step++;
    case 1:
        weapon->base.pos->y += weapon->velocity * speed;
        weapon->velocity -= weapon->gravity * speed;
        cVec_copy3(&to, weapon->base.pos);
        if (ChkLine(&from, &to, &hit, 0, 7, 0x534, 0, 0, 0, 0, 0, 0, 1)) {
            cVec_copy3(weapon->base.pos, &hit);
            SetEffectPos(0x69, 12, 0, weapon->base.pos, -1, 1.0f);
            cOmWeapon_SetBreak(weapon);
        }
        remaining = weapon->lifetime - speed;
        weapon->lifetime = remaining;
        if (remaining <= 0.0f) {
            cOmWeapon_SetBreak(weapon);
            SetEffectPos(0x69, 12, 0, weapon->base.pos, -1, 1.0f);
        }
    }
}
