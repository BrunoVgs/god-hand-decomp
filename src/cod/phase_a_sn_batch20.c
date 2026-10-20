/* Batch 20: seven SN exact clone pairs. */
#include "include_asm.h"
#include "godhand/vu0.h"

INCLUDE_ASM("nonmatching", func_00149400);

INCLUDE_ASM("nonmatching", func_001504B0);

extern void *func_002B6310(void *dst, void *node);
extern void cNode_setLocalTranslation(void *node, void *vec);
extern void StoreVecFromFieldB0_2B6160(void *dst, void *node);

__attribute__((section(".text.func_002F6258")))
void *func_002F6258(void *out, void *node, void *add)
{
    char buf[0x30];
    char *work;

    func_002B6310(buf, node);
    work = buf + 0x20;
    VU0_LQC2(4, buf, 0);
    VU0_SQC2(4, buf, 0x20);
    VU0_VADD_XYZ_IP(buf, 0x20, add);
    VU0_LQC2(4, work, 0);
    VU0_SQC2(4, buf, 0x10);
    cNode_setLocalTranslation(node, buf + 0x10);
    StoreVecFromFieldB0_2B6160(work, node);
    cNode_setLocalTranslation(node, buf);
    VU0_LQC2(4, work, 0);
    VU0_SQC2(4, out, 0);
    return out;
}

__attribute__((section(".text.func_002F71A0")))
void *func_002F71A0(void *out, void *node, void *add)
{
    char buf[0x30];
    char *work;

    func_002B6310(buf, node);
    work = buf + 0x20;
    VU0_LQC2(4, buf, 0);
    VU0_SQC2(4, buf, 0x20);
    VU0_VADD_XYZ_IP(buf, 0x20, add);
    VU0_LQC2(4, work, 0);
    VU0_SQC2(4, buf, 0x10);
    cNode_setLocalTranslation(node, buf + 0x10);
    StoreVecFromFieldB0_2B6160(work, node);
    cNode_setLocalTranslation(node, buf);
    VU0_LQC2(4, work, 0);
    VU0_SQC2(4, out, 0);
    return out;
}

extern void func_0032A8C0(void *obj, int counter);

__attribute__((section(".text.func_00383EB0")))
void func_00383EB0(char *self, char *ctrl)
{
    char *sub = self + 0x3A4;
    int c;
    void *obj;

    if ((*(int *)(ctrl + 0x38) & 0x8000) != 0) {
        c = *(int *)(sub + 0x20);
        if (c < -0xE)
            *(int *)(sub + 0x20) = 0xF;
        else
            *(int *)(sub + 0x20) = c - 1;
        obj = *(void **)(sub + 0x30);
        if (obj != 0)
            func_0032A8C0(obj, *(int *)(sub + 0x20));
    }
    if ((*(int *)(ctrl + 0x38) & 0x2000) != 0) {
        c = *(int *)(sub + 0x20);
        if (c < 0xF)
            *(int *)(sub + 0x20) = c + 1;
        else
            *(int *)(sub + 0x20) = -0xF;
        obj = *(void **)(sub + 0x30);
        if (obj != 0)
            func_0032A8C0(obj, *(int *)(sub + 0x20));
    }
}

__attribute__((section(".text.func_00385410")))
void func_00385410(char *self, char *ctrl)
{
    char *sub = self + 0x484;
    int c;
    void *obj;

    if ((*(int *)(ctrl + 0x38) & 0x8000) != 0) {
        c = *(int *)(sub + 0x20);
        if (c < -0xE)
            *(int *)(sub + 0x20) = 0xF;
        else
            *(int *)(sub + 0x20) = c - 1;
        obj = *(void **)(sub + 0x30);
        if (obj != 0)
            func_0032A8C0(obj, *(int *)(sub + 0x20));
    }
    if ((*(int *)(ctrl + 0x38) & 0x2000) != 0) {
        c = *(int *)(sub + 0x20);
        if (c < 0xF)
            *(int *)(sub + 0x20) = c + 1;
        else
            *(int *)(sub + 0x20) = -0xF;
        obj = *(void **)(sub + 0x30);
        if (obj != 0)
            func_0032A8C0(obj, *(int *)(sub + 0x20));
    }
}

void BlockOwner_dtor(char *self, void *arg);
