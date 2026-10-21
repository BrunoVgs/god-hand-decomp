/* sn-2.95.3-136 matched TU. */
#include "godhand/cNode.h"
#include "godhand/vu0.h"

typedef struct RenderState {
    cVec color;
    cVec position __attribute__((aligned(16)));
    cVec rotation __attribute__((aligned(16)));
    cVec scale;
    float unk1E0;
    int unk1E4, unk1E8;
    signed char unk1EC;
    unsigned char unk1ED, unk1EE, unk1EF;
    int unk1F0;
    char pad1F4[12];
    cVec vector200 __attribute__((aligned(16)));
    short unk210, unk212;
    unsigned char unk214;
    char pad215[3];
    int unk218;
} RenderState;

typedef struct Object {
    cNode node;
    char padF4[0x10];
    int unk104;
    int unk108;
    int unk10C;
    int unk110;
    int unk114;
    int unk118;
    int unk11C;
    int unk120;
    int unk124;
    int unk128;
    int unk12C;
    int unk130;
    int unk134;
    int unk138;
    int unk13C;
    int unk140;
    int unk144;
    int unk148;
    int unk14C;
    int unk150;
    int unk154;
    int unk158;
    int unk15C;
    int unk160;
    int unk164;
    int unk168;
    int unk16C;
    int unk170;
    int unk174;
    int unk178;
    int unk17C;
    int unk180;
    short unk184, unk186, unk188, unk18A, unk18C, unk18E;
    unsigned char unk190;
    char pad191[15];
    RenderState render;
    char pad220[12];
    float unk22C;
    unsigned char unk230;
} Object;

extern cNode *cNode_construct(cNode *, int, cNode *);
extern char D_0044FD58;

// Construct the derived node and initialize its render state.
__attribute__((section(".text.func_00302790")))
Object *func_00302790(Object *object) {
    RenderState *state;
    cVec *scale;
    cNode_construct(&object->node, 0, 0);
    object->unk104 = 0;
    object->node.vt = &D_0044FD58;
    state = &object->render;
    object->unk108 = 0;
    object->unk10C = 0;
    object->unk110 = 0;
    object->unk114 = 0;
    object->unk11C = 0;
    object->unk120 = 0;
    object->unk124 = 0;
    object->unk128 = 0;
    object->unk12C = 0;
    object->unk130 = 0;
    object->unk134 = 0;
    object->unk138 = 0;
    object->unk13C = 0;
    object->unk140 = 0;
    object->unk144 = 0;
    object->unk148 = 0;
    object->unk14C = 0;
    object->unk150 = 0;
    object->unk154 = 0;
    object->unk158 = 0;
    object->unk15C = 0;
    object->unk160 = 0;
    object->unk164 = 0;
    object->unk168 = 0;
    object->unk16C = 0;
    object->unk170 = 0;
    object->unk174 = 0;
    object->unk178 = 0;
    object->unk17C = 0;
    object->unk180 = 0;
    object->unk184 = 0;
    object->unk186 = 0;
    object->unk188 = 0;
    object->unk18A = 0;
    object->unk18E = 0;
    object->unk190 = 0;
    object->render.color.x = 1.0f;
    state->color.y = 1.0f;
    state->color.z = 1.0f;
    state->color.w = 1.0f;
    VU0_SQC2_VF0(object, 0x1B0);
    VU0_SQC2_VF0(object, 0x1C0);
    object->render.scale.x = 1.0f;
    scale = &object->render.scale;
    scale->y = 1.0f;
    scale->z = 1.0f;
    scale->w = 1.0f;
    state->unk1EC = -1;
    state->unk1EF = 255;
    state->unk1E0 = 1.0f;
    state->unk1E4 = 0;
    state->unk1E8 = 0;
    state->unk1ED = 0;
    state->unk1EE = 0;
    state->unk1F0 = 0;
    VU0_SQC2_VF0(object, 0x200);
    state->unk210 = 0;
    state->unk212 = 0;
    state->unk214 = 0;
    state->unk218 = 0;
    object->unk22C = 1.0f;
    object->unk170 = 0;
    object->unk174 = 0;
    object->unk178 = 0;
    object->unk230 = 0;
    return object;
}

