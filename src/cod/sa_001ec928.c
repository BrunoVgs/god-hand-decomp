typedef struct Vec1EC928 {
    float x;
    float y;
    float z;
    float w;
} Vec1EC928;

extern Vec1EC928 D_005681E0;
extern Vec1EC928 D_005681F0;
extern Vec1EC928 D_00568200;
extern Vec1EC928 D_00568210;
extern Vec1EC928 D_00568220;
extern Vec1EC928 D_00568230;

static inline void SetV1EC928(Vec1EC928 *v, float x, float y, float z, float w)
{
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

__attribute__((section(".text.func_001EC928")))
void func_001EC928(int owner, int code)
{
    if (code != 0xFFFF || owner == 0)
        return;
    SetV1EC928(&D_005681E0, 0.45f, -0.21f, 0.95f, 1.0f);
    SetV1EC928(&D_005681F0, 0.0f, -0.20944f, 0.0f, 1.0f);
    SetV1EC928(&D_00568200, 0.0f, 0.0f, 3.0f, 1.0f);
    SetV1EC928(&D_00568210, 0.0f, 0.0f, 0.0f, 1.0f);
    SetV1EC928(&D_00568220, -25.84f, 1.59f, -9.72f, 1.0f);
    SetV1EC928(&D_00568230, -33.13f, 0.22f, -5.92f, 1.0f);
}
