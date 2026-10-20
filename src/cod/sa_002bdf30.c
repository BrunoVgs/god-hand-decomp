/* sn-2.95.3-136, as=sn: NM closer handoff. */
/* sn-2.95.3-136, as=sn: func_002BDF30, split from src/cod/batch29_nm.c by the NM closer. */
#include "godhand/vu0.h"

__attribute__((section(".text.func_002BDF30")))
void *func_002BDF30(void *unused, unsigned short *a1, int n, float thresh)
{
    int i;

    for (i = 0; i < n; i++) {
        if (thresh <= (float)a1[i * 2 + 1])
            return &a1[i * 2];
    }
    return 0;
}

