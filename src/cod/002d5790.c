#include "godhand/heapArena.h"
extern int EnsureInitThenForward_2A9538_30EE08(void *, int, void *);

__attribute__((section(".text.func_002D5790")))
void func_002D5790(char *self)
{
    *(void **)(self + 0x10) = (void *)EnsureInitThenForward_2A9538_30EE08(
        (void *)*(int *)(self + 8), 0x10, &D_00754200);
}
