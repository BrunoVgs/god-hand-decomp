/* sn-2.95.3-136 matched 76-byte Phase A functions. */

#include "godhand/vu0.h"

extern void func_001E8DF0(void *, void *, void *, unsigned short);
extern int func_003069E8(void *, int, void *, void *);
extern int func_0030FB70(void *, void *);
extern int func_0030FE68(void *, void *);
extern int func_00312B00(void *, void *);

__attribute__((section(".text.func_001E87E0")))
void func_001E87E0(char *self, void *a, void *b, unsigned short c)
{
    if (a != 0 && b != 0 && c < 0x16) {
        func_001E8DF0(self, a, b, c);
        *(int *)(self + 4) = 0;
        *(int *)(self + 8) = 0;
        *(int *)(self + 0xC) = 0;
    }
}

__attribute__((section(".text.func_002AE1C8")))
void func_002AE1C8(char *obj)
{
    int count = *(int *)(obj + 0xC);
    int index = 0;
    char *ptrs;
    char *vecs;
    if (count > 0) {
        vecs = obj + 0x30;
        ptrs = obj + 0x20;
        do {
            void *point = *(void **)ptrs;
            VU0_VADD_XYZ_PTR(point, point, vecs);
            index += 1;
            vecs += 0x20;
            ptrs += 0x20;
        } while (index < *(int *)(obj + 0xC));
    }
    *(int *)(obj + 0xC) = 0;
}

__attribute__((section(".text.func_00306C78")))
int func_00306C78(void **table, unsigned int index, void *out1, void *out2)
{
    void *slot;
    *(int *)out1 = 0;
    *(int *)out2 = 0;
    if (index >= 0x40)
        return 0;
    slot = *(void **)((char *)table + (index << 2));
    if (slot == 0)
        return 0;
    return func_003069E8(slot, (int)index, out1, out2) != 0;
}

__attribute__((section(".text.func_0030FAC8")))
int func_0030FAC8(void *object, void *key)
{
    if (func_0030FB70(object, key) == 0)
        return 0;
    return func_0030FE68(object, key);
}

__attribute__((section(".text.func_00312AB0")))
int func_00312AB0(void *object, void *key)
{
    if (func_0030FB70(object, key) == 0)
        return 0;
    return func_00312B00(object, key);
}
