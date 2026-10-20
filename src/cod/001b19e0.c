/* sn-2.95.3-136: reflection matrix and enemy timer (0x1B19E0..). */
#include "godhand/cObjSimple.h"

#include "godhand/cEmManage.h"
#include "godhand/unkObj.h"

__attribute__((section(".text.func_001B19E0")))
void func_001B19E0(void *self, float m[4][4], cObjSimpleVec3 *n)
{
    float xy = -2.0f * n->x * n->y;
    float xz = -2.0f * n->x * n->z;
    float yz = -2.0f * n->y * n->z;

    m[0][0] = 1.0f - 2.0f * n->x * n->x;
    m[1][0] = xy;
    m[2][0] = xz;
    m[3][0] = 0.0f;
    m[0][1] = xy;
    m[1][1] = 1.0f - 2.0f * n->y * n->y;
    m[2][1] = yz;
    m[3][1] = 0.0f;
    m[0][2] = xz;
    m[1][2] = yz;
    m[2][2] = 1.0f - 2.0f * n->z * n->z;
    m[3][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 0.0f;
}
