/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_002009E8, split from src/cod/batch52_nm.c by the NM closer. */
extern void cRoomJump(void *a0);
extern unsigned char D_00583EC0[];

typedef struct { float x, y, z, w; } V4_2009E8;
extern V4_2009E8 D_00583F00[2];

static inline void V4_2009E8_init(V4_2009E8 *v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = 1.0f;
}

__attribute__((section(".text.func_002009E8")))
void func_002009E8(int init, int prio)
{
    if (prio == 0xFFFF) {
        if (init) {
            V4_2009E8 *p;
            { unsigned char *b = D_00583EC0; cRoomJump(b + 0x34); }
            p = D_00583F00;
            V4_2009E8_init(p, 0.66f, 0.01f, -52.4f);
            p++;
            V4_2009E8_init(p, -48.0f, 0.25f, -57.3f);
        }
    }
}
