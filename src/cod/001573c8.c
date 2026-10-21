#include "godhand/cOmBase.h"

/* 1 when pt lies inside the quad a-b-c-d on the XZ plane. */
__attribute__((section(".text.func_001573C8")))
int func_001573C8(float *pt, cVec *a, cVec *b, cVec *c, cVec *d)
{
    float ox = a->x;
    float oz = a->z;
    float px = pt[0] - ox;
    float pz = pt[2] - oz;
    float bx = b->x - ox;
    float bz = b->z - oz;
    float dx = d->x - ox;
    float dz = d->z - oz;
    float cx, cz;

    if (bz * px < bx * pz || dx * pz < dz * px) {
        return 0;
    }
    cx = c->x - ox;
    cz = c->z - oz;
    px -= cx;
    pz -= cz;
    bx -= cx;
    bz -= cz;
    dx -= cx;
    dz -= cz;
    if (bx * pz < bz * px || dx * pz > dz * px) {
        return 0;
    }
    return 1;
}

