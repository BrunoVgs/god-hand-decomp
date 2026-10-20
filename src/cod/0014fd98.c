#include "godhand/cGameObj.h"
__attribute__((section(".text.cObjBaseArray_SearchOM")))
void *cObjBaseArray_SearchOM(char *arr, long mask)
{
    char *v = *(char **)arr;
    char **cur;

    for (cur = *(char ***)(v + 4); cur < *(char ***)(v + 8); cur++) {
        char *o = *cur;
        if ((cGameObj_idInRange((cGameObj *)o, 0x300, 0x500) & 0xFF) && *(long *)(o + 0x538) == mask)
            return o;
    }
    return 0;
}
