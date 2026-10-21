/* sn-2.95.3-136 matched TU. */
#include "godhand/SmoData.h"

/* Bind an SMO data block to the reader. Returns 1 when the block is valid,
   else clears the reader and returns 0. */
__attribute__((section(".text.func_001C3C58")))
int func_001C3C58(SmoReader *rd, SmoHeader *hdr) {
    if (hdr == 0) return 0;
    rd->hdr = hdr;
    if (hdr->magic != SMO_MAGIC) {
        rd->hdr = 0;
        return 0;
    }
    if (hdr->count == 0) {
        rd->hdr = 0;
        return 0;
    }
    if (hdr->version < SMO_VERSION_LONG)
        rd->body = &hdr->body[0];
    else
        rd->body = &hdr->body[1];
    return 1;
}
