/* sn-2.95.3-136 matched TU. */
#include "godhand/DataPack.h"

#define BLOCK_BYTES  0x70   /* buffer bytes per block of DATAPACK_ITEMS_PER_BLOCK items */

/* Size of the buffer section idx needs: one BLOCK_BYTES block per 24 items,
   rounded up, plus the buffer header. */
__attribute__((section(".text.DataPack_calcBufSize70")))
int DataPack_calcBufSize70(DataPackOwner *self, int idx) {
    DataPackRef ref;
    int count;
    int size;

    ref.pack = self->pack;
    ref.sect = (DataPackSection *)(ref.pack->offs[idx] + (int)ref.pack);
    count = ref.sect->count;
    if (count % DATAPACK_ITEMS_PER_BLOCK) {
        size = count / DATAPACK_ITEMS_PER_BLOCK + 1;
    } else {
        size = count / DATAPACK_ITEMS_PER_BLOCK;
    }
    size *= BLOCK_BYTES;
    return size + DATAPACK_BUF_HEADER;
}
