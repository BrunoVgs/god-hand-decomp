#include "godhand/vu0.h"

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
