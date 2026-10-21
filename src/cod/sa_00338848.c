/* cygnus-2.96 matched TU. */
#include "godhand/criStm.h"
extern char D_004557C8[];
/* Report unsupported sample widths when the RNA backend is active. */
__attribute__((section(".text.func_00338848")))
int func_00338848(long unused, long bitsPerSample) {
    if (((D_003E0710 != 1) || (D_003E0708 > 0)) && bitsPerSample != 16)
        func_003260C8(D_004557C8, bitsPerSample);
}
