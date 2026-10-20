#include "godhand/vu0.h"

extern void func_001E8DF0(void *, void *, void *, unsigned short);

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
