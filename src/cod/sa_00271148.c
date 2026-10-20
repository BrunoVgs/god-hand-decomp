/* sn-2.95.3-136, as=sn: NM closer handoff. */
/* func_00271148 (sn-2.95.3-136): written like func_00271298 (zero local, copies into the abs temps, m reused). */

extern char *Getplayer(void);
extern float Turn_dest(void *a0, void *a1, float f12, float f13);
extern void func_002DC260(char *self);
extern void func_002DC5E0(char *self);

static inline float Absf(float x)
{
    if (x < 0.0f) {
        return -x;
    }
    return x;
}

__attribute__((section(".text.func_00271148")))
void func_00271148(char *self)
{
    char *g;
    char *q;
    float z;
    float r;
    float t;
    float m;
    float dy;
    float u;

    g = (char *)Getplayer();
    z = 0.0f;
    if (*(float *)(g + 0x54C) > z) return;
    if (*(int *)(g + 0x6A0) != 0) return;
    q = *(char **)((char *)Getplayer() + 0xF0);
    dy = Turn_dest(q, *(char **)(self + 0xF0),
                   *(float *)((char *)Getplayer() + 0x104),
                   3.1415927f);
    r = dy;
    if (r < z) t = -r; else t = r;
    if (t < 1.7453293f) return;
    m = *(float *)(*(int *)(g + 0xF0) + 4) - *(float *)(*(int *)(self + 0xF0) + 4);
    dy = m;
    if (dy < z) u = -dy; else u = dy;
    if (u > 0.5f) return;
    m = *(float *)(self + 0x618);
    if (m < 4.0f) {
        if (*(int *)(self + 0x564) != 0x20F) {
            func_002DC260(self);
        } else {
            func_002DC5E0(self);
        }
    }
}
