/* sn-2.95.3-136: copy the B0 field vector to 0x2B0, scale 0x110->0x18C by 0.01. */
extern void *StoreVecFromFieldB0_2B6160(void *dst, void *self);

static inline void Copy3(float *d, float *s)
{
    if (d != s) {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
}

__attribute__((section(".text.func_002F6B40")))
int func_002F6B40(char *self)
{
    float v[4];

    StoreVecFromFieldB0_2B6160(v, self);
    Copy3((float *)(self + 0x2B0), v);
    *(float *)(self + 0x2C0) = (float)*(unsigned char *)(*(char **)(self + 0x110) + 0x18C) * 0.01f;
    return 1;
}
