#include "godhand/vu0.h"

extern int func_0030FCC0(void *a0);

__attribute__((section(".text.func_0030FB20")))
void *func_0030FB20(void *unused, char *obj)
{
    if (obj != 0) {
        if (func_0030FCC0(obj) != 0)
            return obj;
        {
            char *vt = *(char **)(obj + 0x214);
            (*(void (**)(void *, int))(vt + 0xC))(obj + *(short *)(vt + 8), 3);
        }
    }
    return 0;
}

