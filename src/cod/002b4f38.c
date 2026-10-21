#include "godhand/cCoreSave.h"

static inline unsigned char slotUsed(char *p)
{
    if (*(int *)p != 0)
        return 1;
    return 0;
}

__attribute__((section(".text.func_002B4F38")))
int func_002B4F38(int **a0)
{
    char *p = (char *)*a0;
    int count = 0;

    for (;;) {
        if (!slotUsed(p))
            return count;
        count++;
        if (count >= 3)
            return -1;
        p += 0xAC;
    }
}

