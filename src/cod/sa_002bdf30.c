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

