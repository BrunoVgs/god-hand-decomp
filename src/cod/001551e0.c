/* sn-2.95.3-136 matched TU. */
#include "godhand/mdlPkt.h"

#define BLOCK_BYTES  0x90   /* packet bytes per block of MDL_PKT_VTX_PER_BLOCK vertices */

/* Packet size for record idx of the model pack: one BLOCK_BYTES block per
   24 vertices, rounded up, plus the packet header. */
__attribute__((section(".text.DataPack_calcBufSize90")))
int DataPack_calcBufSize90(MdlObj *self, int idx) {
    PackRef ref;
    int nVtx;
    int size;

    ref.base = self->pack;
    ref.rec = (MdlRec *)(ref.base->ofs[idx] + (int)ref.base);
    nVtx = ref.rec->nVtx;
    if (nVtx % MDL_PKT_VTX_PER_BLOCK) {
        size = nVtx / MDL_PKT_VTX_PER_BLOCK + 1;
    } else {
        size = nVtx / MDL_PKT_VTX_PER_BLOCK;
    }
    size *= BLOCK_BYTES;
    return size + MDL_PKT_HEADER;
}
