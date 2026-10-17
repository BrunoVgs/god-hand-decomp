#include "godhand/vu0.h"

/* func_002B6080 — zero a stack vector, run cNode_updateWorldMatrix(a1), fetch the scale
 * vector of the matrix at a1+0xB0 into the stack buffer, copy it to a0, and
 * return a0.  sn-2.95.3-136. */

extern void cNode_updateWorldMatrix(void *);
extern void MtxGetScaleVec(void *, void *);

__attribute__((section(".text.func_002B6080")))
void *func_002B6080(void *a0, void *a1) {
    unsigned char buf[16] __attribute__((aligned(16)));
    VU0_SQC2_VF0(buf, 0);
    cNode_updateWorldMatrix(a1);
    MtxGetScaleVec(buf, (char *)a1 + 0xB0);
    VU0_LQC2(4, buf, 0);
    VU0_SQC2(4, a0, 0);
    return a0;
}
