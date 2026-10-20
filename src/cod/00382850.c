/* func_00382850 / func_00383280: identical "any flag set" scans over a counted byte list. */

#include "godhand/flagList.h"

__attribute__((section(".text.func_00382850")))
int func_00382850(void *self, FlagList *list)
{
    int i;

    for (i = 0; i < list->count; i++) {
        if (list->flag[i + 1])
            return 1;
    }
    return 0;
}

__attribute__((section(".text.func_00383280")))
int func_00383280(void *self, FlagList *list)
{
    int i;

    for (i = 0; i < list->count; i++) {
        if (list->flag[i + 1])
            return 1;
    }
    return 0;
}
