/* sn-2.95.3-136 matched TU. */
#include "godhand/cOmBase.h"
#include "godhand/vu0.h"
extern char D_005FEE00[];
extern int cSnd_SeCall_2CB8A0(void *a0, int a1, short a2, short a3, short a4, int a5, int a6);
extern char D_00586AB0[];
extern void cEmSetParam_setEm(void *a0, int a1);
extern void cEmWrap_setPos_2959B0(void *a0, cVec *pos);
extern void cEmWrap_StartAction(void *a0);
extern void cEmWrap_SetKeepPos(void *a0, cVec *pos);
extern void cEmWrap_setMutekiTimer(void *a0, float time);
extern void cEmSetParam_updateSetDataPos(void *a0, int index, cVec *pos);
extern void cEmSetParam_updateSetDataAppPattern(void *a0, int index, unsigned int pattern);

/* vu0.h additions */
/* Store a VU0 quadword directly to a C memory operand. */
#define VU0_SQC2_MEM(reg, var) __asm__ __volatile__(".set push\n.set noreorder\nsqc2 $vf" #reg ", %0\n.set pop\n" : : "m"(var) : "memory")

typedef struct SpawnObject {
    char pad[0xF0];
    cVec *pos;
    char padF4[0x50C];
    unsigned char slots[16];
    unsigned char pad610;
    unsigned char cursor;
    unsigned char remaining;
    unsigned char pad613[2];
    unsigned char pending;
    char pad616[6];
    float height;
} SpawnObject;

/* Release queued enemies at the current object position. */
__attribute__((section(".text.func_001A7F58")))
int func_001A7F58(SpawnObject *object)
{
    unsigned char enemy[16] __attribute__((aligned(16)));
    cVec keep __attribute__((aligned(16)));
    unsigned char start, before;
    unsigned int index;
    unsigned char *slot;
    unsigned char *slots;
    if (object->remaining == 0)
        return 0;
    if (object->pending == 0)
        return 0;
    cSnd_SeCall_2CB8A0(D_005FEE00, 2, 0x33, -1, -1, 0, 0);
    start = object->cursor;
    before = object->pending;
    index = start;
    if (before != 0) {
        slots = object->slots;
        do {
            slot = slots + index;
            if (*slot != 0xFF) {
                enemy[0] = *slot;
                cEmSetParam_setEm(D_00586AB0, enemy[0]);
                cEmWrap_setPos_2959B0(enemy, object->pos);
                cEmWrap_StartAction(enemy);
                VU0_LQC2(4, object->pos, 0);
                VU0_SQC2_MEM(4, keep);
                keep.y = object->height;
                cEmWrap_SetKeepPos(enemy, &keep);
                cEmWrap_setMutekiTimer(enemy, 30.0f);
                cEmSetParam_updateSetDataPos(D_00586AB0, *slot, &keep);
                cEmSetParam_updateSetDataAppPattern(D_00586AB0, *slot, 0);
                *slot = 0xFF;
                object->cursor = index;
                object->pending--;
                if (--object->remaining == 0)
                    break;
            }
            index++;
            if (index >= 16)
                index = 0;
            if (start == index)
                break;
        } while (object->pending != 0);
    }
    return before - object->pending;
}
