/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: GIF tag pair into a model packet (0x155AE8). */
#include "godhand/mdlPkt.h"


#define TAG64(e) ((unsigned int)((e).w1 | 0x30000000) | ((unsigned long)((e).w0 & 0x0FFFFFFF) << 32))

__attribute__((section(".text.func_00155AE8")))
void func_00155AE8(Pkt0B0 *pkt, int id, int buf)
{
    if (id >= 0) {
        id = (unsigned char)id;
        pkt[buf].q[14] = TAG64(D_004A5D80[id]);
        pkt[buf].q[16] = TAG64(D_004A5D80[id + 1]);
    } else {
        id = (unsigned char)id;
        pkt[buf].q[14] = 0x10000000;
        pkt[buf].q[16] = TAG64(D_004A5D80[id + 1]);
    }
}
