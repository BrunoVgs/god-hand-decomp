/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"
#include "godhand/vu0.h"

extern void func_002B6310(cVec *out, void *node);
extern void StoreVecFromFieldB0_2B6160(cVec *dst, void *node);
extern void cCamera_getScreenPos(cVec *out, void *camera, cVec *pos);
extern void cNode_setLocalTranslation(void *node, cVec *v);
extern void LinkObj_callLockOn(void *node);
extern void *D_005CAFF0;
extern float cEmManage_GetSpeedRate(void *manager);
extern void func_0031A0B8(void *obj, int a);
extern void func_0031A088(void *obj, int a);
extern void sceVu0ApplyMatrix(cVec *dst, void *mtx, cVec *src);
extern void ClearFields_20_24_28_30_1FC7F8(void *node);

#define NODE_LOCKED     0x01000000      /* LockNode.flags: the node is locked on */

/* A scene node with a flag word at 0x11C. */
typedef struct LockNode {
    char unk000[0x11C];
    unsigned int flags;                 /* 0x11C */
} LockNode;

/* If the node's position projects in front of the camera, unlock it, move it to the screen position, call the lock-on,
 * then lock it and put it back at its original place. */
__attribute__((section(".text.cNode_lockOnScreen")))
void cNode_lockOnScreen(LockNode *node) {
    cVec orig;
    cVec field;
    cVec screen;

    func_002B6310(&orig, node);
    StoreVecFromFieldB0_2B6160(&field, node);
    cCamera_getScreenPos(&screen, D_005CAFF0, &field);
    if (0.0f < screen.z) {
        node->flags &= ~NODE_LOCKED;
        cNode_setLocalTranslation(node, &screen);
        LinkObj_callLockOn(node);
        node->flags |= NODE_LOCKED;
        cNode_setLocalTranslation(node, &orig);
    }
}

extern int D_005864F0;                  /* enemy manager */

/* An actor that drifts: a velocity pair at 0x630 and 0x674 and a countdown at 0x660 past cOmBase. */
typedef struct DriftObj {
    cOmBase base;                       /* 0x000 */
    char unk5E0[0x50];
    float velA;                         /* 0x630 */
    char unk634[0x2C];
    float timeLeft;                     /* 0x660 */
    char unk664[0x10];
    float velB;                         /* 0x674 */
} DriftObj;

/* Step 0 starts the drift (velocity +-0.0128, 15 frames) and runs step 1; step 1 moves the actor along y by the
 * velocity, advances the velocities and the countdown by the frame rate, and when the countdown ends goes back to mode 1. */
__attribute__((section(".text.cOmBase_stepDrift")))
void cOmBase_stepDrift(DriftObj *self) {
    float rate = cEmManage_GetSpeedRate(&D_005864F0);
    switch (self->base.step) {
    case 0: {
        float v = 0.013f;
        self->velA = v;
        self->timeLeft = 15.0f;
        self->velB = -v;
        self->base.step = self->base.step + 1;
    }
    /* falls through */
    case 1:
        self->base.pos->y = self->base.pos->y + self->velB * rate;
        self->timeLeft = self->timeLeft - rate;
        self->velB = self->velB - self->velA * rate;
        if (self->timeLeft <= 0.0f) {
            self->base.mode = 1;
            self->base.phase = 0;
            self->base.step = 0;
            self->base.stepArg = 0;
        }
        break;
    }
}

/* The object a controller steers: a vector at 0x340. */
typedef struct SteerTarget {
    char unk000[0x340];
    cVec dir;                           /* 0x340 */
} SteerTarget;

/* A controller: a target object at 0 and the last x value at 0xB8. */
typedef struct SteerCtl {
    SteerTarget *target;                /* 0x00 */
    char unk04[0xB4];
    float x;                            /* 0xB8 */
} SteerCtl;

/* Store x, and when there is a target set its direction to (x, 0, 0) and run func_0031A088 unless that direction is zero. */
__attribute__((section(".text.cObj_setFloatAndVec")))
void cObj_setFloatAndVec(SteerCtl *self, float x) {
    SteerTarget *target = self->target;
    cVec v;

    if (target == 0) {
        return;
    }
    self->x = x;
    v.w = 1.0f;
    v.x = x;
    v.y = 0.0f;
    v.z = 0.0f;
    cVec_copy3(&target->dir, &v);
    func_0031A0B8(target, 3);
    if (v.x != 0.0f || v.y != 0.0f || v.z != 0.0f) {
        func_0031A088(target, 3);
    }
}

typedef struct VtEnt {
    short delta;
    short index;
    void (*pfn)(cVec *out, void *self);
} VtEnt;

/* A node with a rotation matrix at 0x70, a virtual part at 0x100 and a position at 0x120. */
typedef struct LiftNode {
    char unk000[0x70];
    void *mtx;                          /* 0x070 */
    char unk074[0x8C];
    VtEnt *part;                        /* 0x100 */
    char unk104[0x1C];
    cVec pos;                           /* 0x120 */
} LiftNode;

#define PART_BOX_ENTRY  6               /* the part's table entry that returns its box vector */

/* Ask the part (a virtual call) for its box vector, put half its height on the y axis, rotate that by the matrix and
 * store the result as the position. buf[0] is the lift, buf[1] the box, buf[2] the rotated lift. */
__attribute__((section(".text.cNode_updateLiftedPos")))
void cNode_updateLiftedPos(LiftNode *self) {
    cVec buf[3];
    VtEnt *vt = self->part;
    cVec *rot;
    void *mtx;

    vt[PART_BOX_ENTRY].pfn(&buf[1], (char *)self + vt[PART_BOX_ENTRY].delta);
    rot = &buf[2];
    mtx = self->mtx;
    buf[0].x = 0.0f;
    buf[0].y = buf[1].y * 0.5f;
    buf[0].z = 0.0f;
    buf[0].w = 1.0f;
    VU0_LQC2(4, buf, 0);
    VU0_SQC2(4, buf, 0x20);
    sceVu0ApplyMatrix(rot, mtx, rot);
    VU0_LQC2(4, rot, 0);
    VU0_SQC2(4, buf, 0x10);
    cVec_copy3(&self->pos, &buf[1]);
}

/* A node of a doubly linked list. */
typedef struct LinkNode {
    char unk00[0x20];
    struct LinkNode *prev;              /* 0x20 */
    struct LinkNode *next;              /* 0x24 */
} LinkNode;

/* An owner whose list head is at 0x3C. */
typedef struct LinkOwner {
    char unk00[0x3C];
    LinkNode *head;                     /* 0x3C */
} LinkOwner;

/* Release every node on the list: unlink the head from its neighbours and clear it. Returns 0 if one cannot be released. */
__attribute__((section(".text.cDvd_releaseAll")))
int cDvd_releaseAll(LinkOwner *self) {
    LinkNode *node;
    if ((node = self->head) != 0) {
        do {
            if (func_001FCBA0(self->head) == 0) {
                return 0;
            }
            node = self->head;
            self->head = node->next;
            if (node->prev != 0) {
                node->prev->next = node->next;
            }
            if (node->next != 0) {
                node->next->prev = node->prev;
            }
            ClearFields_20_24_28_30_1FC7F8(node);
        } while (self->head != 0);
    }
    return 1;
}
