typedef union {
    float f;
    unsigned int u;
} FloatBits;

typedef struct {
    long v0;
    char pad0[0x18];
    long v20;
    char pad1[0x18];
    long v40;
    char pad2[0x18];
    long v60;
    char pad3[0x18];
    long v80;
} FloatRows;


__attribute__((section(".text.func_0015EEE0")))
void func_0015EEE0(FloatRows *p)
{
    FloatBits bits;
    bits.f = 1.0f;
    p->v20 = 0;
    p->v80 = 0;
    p->v60 = 0;
    p->v40 = 0;
    p->v0 = (long)bits.u << 32;
}
