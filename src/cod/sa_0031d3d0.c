/* sn-2.95.3-136: stage set-data mesh placement (0x31D3D0). */

#include "godhand/stageSet.h"

extern char *CreateObj(int id, int a1);
extern void *__dynamic_cast(int tf, void *dst, int bool_ptr, void *obj, void *src, void *ptr);
extern void func_00319FC8(void);
extern void func_0014E8D8(void);
extern int D_00747A9C;
extern char D_00754C50[];
extern void Adjust_theta_vec(float *v);
extern void func_0014C328(char *obj);
extern void cModel_calcParts(char *obj);
extern void func_003129D0(char *list, char *obj);

static inline int MeshHideFlag(unsigned char hide)
{
    return hide ? 0x2000000 : 0;
}

static inline char *CastSetObj(char *raw)
{
    char *vt;

    return raw == 0
        ? 0
        : (vt = *(char **)(raw + 0x214),
           __dynamic_cast(*(int *)(vt + 4), func_00319FC8, 1, raw + *(short *)vt, func_0014E8D8, raw));
}

static __inline__ void SetVec4xyz(float *d, float x, float y, float z)
{
    d[0] = x;
    d[1] = y;
    d[2] = z;
    d[3] = 1.0f;
}

static inline void SetVec4(float *dst, float *v)
{
    if (dst != v) {
        dst[0] = v[0];
        dst[1] = v[1];
        dst[2] = v[2];
    }
}

__attribute__((section(".text.func_0031D3D0")))
void func_0031D3D0(SetData *set, int mesh, int arg2, unsigned char hide)
{
    int key[4];
    BoundingBox box;
    float v[4];
    char *raw;
    char *obj;
    char *state;
    unsigned char unk43;
    char *vt;
    int flags;

    raw = CreateObj(0, 0xFFFF);
    if (raw == 0) {
        obj = 0;
    } else {
        obj = CastSetObj(raw);
    }
    key[0] = mesh;
    flags = MeshHideFlag(hide) | 0x1000;
    unk43 = set->unk43;
    state = GetActiveState_149310();
    flags |= 0x1000000;
    cBoundingBox(&box);
    func_00148420(state, mesh, 0, flags, 1, &box, 0);
    cModel_addMesh(obj, state, &box);
    *(SetData **)(state + 0x414) = set;
    *(SetData **)(obj + 0x320) = set;
    if (D_00747A9C != 0) {
        *(int *)(obj + 0x250) |= 0x400080;
    }
    if ((*(SetData **)(obj + 0x320))->flags & 0x400000) {
        func_0031D2B8(mesh, 0);
    }
    *(int *)(obj + 0x2F8) = arg2;
    *(unsigned char *)(obj + 0x2FD) = unk43;
    *(int *)(obj + 0x250) |= 0x400;
    SetVec4xyz(v, set->pos[0], set->pos[1], set->pos[2]);
    SetVec4((float *)(obj + 0x110), v);
    SetVec4xyz(v, set->rot[0], set->rot[1], set->rot[2]);
    SetVec4((float *)(obj + 0x100), v);
    SetVec4xyz(v, set->scale[0], set->scale[1], set->scale[2]);
    SetVec4(*(float **)(obj + 0xF0), v);
    Adjust_theta_vec((float *)(obj + 0x100));
    func_0014C328(obj);
    vt = *(char **)(obj + 0x214);
    (*(int (**)())(vt + 0x44))(obj + *(short *)(vt + 0x40));
    cModel_calcParts(obj);
    if (*(unsigned int *)(obj + 0x350) & 0x20000000) {
        func_003129D0(D_00754C50, obj);
    }
    func_001F8A60(&box, 2);
}

