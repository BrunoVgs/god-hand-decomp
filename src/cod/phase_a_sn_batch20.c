/* Batch 20: seven SN exact clone pairs. */
#include "godhand/vu0.h"

extern void EntList_destroy(void *self);
extern void List_destroyChildren(void *self);
extern int func_002A96C0(int stride, int count, int align);
extern void *EnsureInitThenForward_2A9538_30EE08(int size, int align, void *region);
extern void func_002A96D8(void *self, void *buf, int stride, int count, int align);
extern void *D_003C3CF0;

__attribute__((section(".text.func_00149400")))
void func_00149400(void *self, int count)
{
    int size;
    void *buf;

    EntList_destroy(self);
    size = func_002A96C0(0x480, count, 0x80);
    buf = EnsureInitThenForward_2A9538_30EE08(size, 0x80, D_003C3CF0);
    func_002A96D8(self, buf, 0x480, count, 0x80);
    {
        volatile int *p = (volatile int *)self;
        p[0x20 / 4] = size;
        p[0x24 / 4] = count;
        p[0x18 / 4] = count;
        p[0x1C / 4] = count;
    }
}

__attribute__((section(".text.func_001504B0")))
void func_001504B0(void *self, int count)
{
    int size;
    void *buf;

    List_destroyChildren(self);
    size = func_002A96C0(0x220, count, 0x10);
    buf = EnsureInitThenForward_2A9538_30EE08(size, 0x10, D_003C3CF0);
    func_002A96D8(self, buf, 0x220, count, 0x10);
    {
        volatile int *p = (volatile int *)self;
        p[0x20 / 4] = size;
        p[0x24 / 4] = count;
        p[0x18 / 4] = count;
        p[0x1C / 4] = count;
    }
}

extern void func_001C7D98(void *self);
extern void InitFields_1B6E90(void *self);
extern void Obj0000_Set_Byte_54(void *slot, int v);
extern int D_00423E48;
extern int D_004272F8;

extern char D_003BDD08[];
extern char D_003BDE98[];

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

extern void displayScrollLayer(int layer, int on);

extern void cHeap_free(void *heap, void *block);
extern void func_002FBE28(void *self, void *arg);
extern char D_0044E300[];
extern char D_0044E960[];
void BlockOwner_dtor(char *self, void *arg);
