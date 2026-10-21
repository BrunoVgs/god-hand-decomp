/* cygnus-2.96 matched TU. */
#include "godhand/EntryPool.h"

extern int D_003E0708;          /* pool size */
extern PoolEntry D_003E0768[];  /* pool entries */

/* Claim the first free pool entry and return it, or 0 when the pool is full. */
__attribute__((section(".text.func_00337320")))
PoolEntry *func_00337320(void) {
    int i;
    PoolEntry *e;

    e = 0;
    for (i = 0; i < D_003E0708; i++) {
        e = &D_003E0768[i];
        if (e->used == 0) {
            break;
        }
    }
    if (i == D_003E0708) {
        return 0;
    }
    e->used = 1;
    return e;
}
