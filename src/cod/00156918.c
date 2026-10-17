/* ee-2.9-991111 matched TU. */

#include "godhand/vu0.h"

/* Which side of the line a-b the point c lies on (in the x,y plane):
 * 1 left, -1 right, 0 on the line. */
__attribute__((section(".text.chack_point_line")))
int chack_point_line(float *a, float *b, float *c)
{
    float buf[8];
    float cross;
    VU0_SQC2_VF0(buf, 0x00);
    VU0_SQC2_VF0(buf, 0x10);
    buf[0] = b[0] - a[0];
    buf[1] = b[1] - a[1];
    buf[4] = c[0] - a[0];
    buf[5] = c[1] - a[1];
    cross = buf[0] * buf[5] - buf[1] * buf[4];
    if (cross > 0.0f) {
        return 1;
    }
    if (cross < 0.0f) {
        return -1;
    }
    return 0;
}
