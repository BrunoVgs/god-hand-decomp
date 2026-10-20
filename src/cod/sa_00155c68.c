/* sn-2.95.3-136: GIF tag pair into two out-params (0x155C68). */
#include "godhand/mdlPkt.h"

__attribute__((section(".text.func_00155C68")))
void func_00155C68(unsigned long *a0, unsigned long *a1, int id)
{
    if (id >= 0) {
        id = (unsigned char)id;
        *a0 = TAG64(D_004A5D80[id]);
        *a1 = TAG64(D_004A5D80[id + 1]);
    } else {
        id = (unsigned char)id;
        *a0 = 0x10000000;
        *a1 = TAG64(D_004A5D80[id + 1]);
    }
}
