/* cygnus-2.96 matched TU. */
#include "godhand/criStm.h"

extern char D_004557C8[];   /* "PS2RNA_SetBitPerSmpl: not support %d bps\n" */

/* Warn when a sample width other than 16 bits is requested while the stream pool is in use. */
__attribute__((section(".text.func_00338848")))
int func_00338848(long handle, long bitsPerSample) {
    if ((D_003E0710 != CRISTM_POOL_CONFIGURED || D_003E0708 > 0) &&
        bitsPerSample != PS2RNA_BITS_PER_SAMPLE) {
        func_003260C8(D_004557C8, bitsPerSample);
    }
}
