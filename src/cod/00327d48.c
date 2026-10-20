/* cygnus-2.96: stream/SFD/sound singletons. */
#include "godhand/criStm.h"

extern int func_00327B58(int a0, int a1, int a2, void *a3);
extern int func_00327C30(int a0, int a1, int a2, void *a3);

__attribute__((section(".text.func_00327D48")))
void func_00327D48(void *p, int n)
{
    long r;

    if (n < 0x100) {
        r = func_00327B58(0, 0, 0, p);
    } else {
        r = func_00327C30(0, 0, 0, p);
    }
}
