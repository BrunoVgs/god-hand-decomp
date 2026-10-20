#include "godhand/cDataManager.h"
extern void cDataSlot_resetSeHandles(void *);

__attribute__((section(".text.func_001FF448")))
void func_001FF448(cDataSlot *object)
{
    if (object->useCount >= 0)
        cDataSlot_resetSeHandles(object);
}
