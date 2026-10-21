/* sn-2.95.3-136 matched TU. */
#include "godhand/seqNode.h"
/* Advance the enabled sequence links whose counters are running. */
__attribute__((section(".text.func_0037CA98")))
void func_0037CA98(void) {
    SeqLink *link = D_0076C8C0;
    unsigned int stopped = 0xFFFFFFFFU;
    int remaining = SEQ_NUM - 1;
    do {
        --remaining;
        if (link->flags != 0) {
            unsigned int counter = *(unsigned int *)link->unk0C;
            if (counter != stopped)
                *(unsigned int *)link->unk0C = counter + 1;
        }
        ++link;
    } while (remaining >= 0);
}
