#include "godhand/vu0.h"

extern int func_0030FB70(void *, void *);
extern int func_00312B00(void *, void *);

__attribute__((section(".text.func_00312AB0")))
int func_00312AB0(void *object, void *key)
{
    if (func_0030FB70(object, key) == 0)
        return 0;
    return func_00312B00(object, key);
}
