/* sn-2.95.3-136 matched TU. */
#include "godhand/ResPack.h"

/* Return entry nth among the pack entries named *nameA or *nameB, counting
   from 0, or 0 when there are not that many. */
__attribute__((section(".text.func_0031CDC0")))
int func_0031CDC0(ResPack *pack, unsigned int *nameA, unsigned int *nameB, int nth) {
    int found;
    unsigned int i;
    unsigned int n;
    unsigned int *name;
    unsigned int v;

    if (pack == 0) {
        return 0;
    }
    n = pack->count;
    found = 0;
    name = &pack->count + n;
    for (i = 1; i <= n; i++) {
        v = *++name;
        if (v == *nameA || v == *nameB) {
            if (found == nth) {
                return (&pack->count)[i] + (int)pack;
            }
            found++;
        }
    }
    return 0;
}
