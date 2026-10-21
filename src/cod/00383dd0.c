/* sn-2.95.3-136 matched TU. */
#include "godhand/MixChannel.h"

/* Return 1 when every channel level in the chosen array (levelB if useB)
   equals the level of the selected channel, else 0. */
__attribute__((section(".text.func_00383DD0")))
int func_00383DD0(void *owner, MixChannel *mix, unsigned char useB) {
    short *level;
    int i;

    level = mix->levelA;
    if (useB) {
        level = mix->levelB;
    }
    for (i = 0; i < mix->chCount; i++) {
        if (i != mix->sel - 1) {
            if (level[i + 1] != level[mix->sel]) {
                return 0;
            }
        }
    }
    return 1;
}
