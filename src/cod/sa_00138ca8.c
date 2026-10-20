/* SN ProDG ee-gcc 2.95.3: func_00138CA8, copies the selected camera state parts from src to dst: bit 0 the
 * vector at +0x210, bit 1 the vector at +0x200, bit 3 the 0x360-byte block at the start. */
typedef struct { float x, y, z; } CamVec3;
typedef struct { int q[4]; } __attribute__((aligned(16))) CamQ;
typedef struct { CamQ q[0x36]; } CamBlock;

static inline void CamVec3_set(CamVec3 *d, CamVec3 *s)
{
    if (d != s) {
        d->x = s->x;
        d->y = s->y;
        d->z = s->z;
    }
}

__attribute__((section(".text.func_00138CA8")))
void func_00138CA8(void *a0, char *dst, char *src, unsigned char mask)
{
    if (mask & 1)
        CamVec3_set((CamVec3 *)(dst + 0x210), (CamVec3 *)(src + 0x210));
    if (mask & 2)
        CamVec3_set((CamVec3 *)(dst + 0x200), (CamVec3 *)(src + 0x200));
    if (mask & 8)
        *(CamBlock *)dst = *(CamBlock *)src;
}
