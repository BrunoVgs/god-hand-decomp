#include "godhand/vu0.h"

typedef struct {
    char bytes[16];
} QWord;

extern QWord D_0061B660;

/* Zero the quadword D_0061B660 when type is 0xFFFF and enabled is set. */
__attribute__((section(".text.func_002F1AA0")))
void func_002F1AA0(int enabled, unsigned int type)
{
    if (type == 0xFFFF && enabled != 0) {
        VU0_SQC2_VF0_AT(D_0061B660);
    }
}
