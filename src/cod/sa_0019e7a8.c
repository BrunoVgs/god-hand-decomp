/* sn-2.95.3-136: enemy setup with a damage-take volume, then the enemy work defaults (0x19DD30);
 * volume build as SpawnDamageTakeVolumeE. func_001C28A0 takes only self (it clobbers a1/a2 at once). */
#include "godhand/emDamageVol.h"

extern void func_001B6FB8(char *p);
extern void *cDamageManage_CreateDamageTake(void *mgr, void *owner, int kind);
extern void func_001FD9D8(void *slot, void *mtx, float *ofs, float *rot, float *size);
extern char D_00574380[];

__attribute__((section(".text.func_0019E7A8")))
int func_0019E7A8(char *p)
{
    float f[16];
    float *m;
    float *nv;
    float *t;
    void *slot;
    float one, ca, cb;

    func_001B6FB8(p);
    one = 1.0f;
    ca = 0.8f;
    cb = 1.15f;
    t = &f[4];
    m = &f[8];
    f[0] = ca;
    f[1] = cb;
    f[2] = ca;
    f[5] = cb;
    f[3] = one;
    f[4] = ca;
    f[6] = ca;
    t[3] = one;
    f[8] = 0.0f;
    f[9] = 0.0f;
    f[10] = 0.0f;
    m[3] = one;
    slot = cDamageManage_CreateDamageTake(D_00574380, p, 2);
    *(void **)(p + EM_DMG_TAKE) = slot;
    if (slot != 0) {
        nv = &f[12];
        f[12] = 0.0f;
        f[13] = 0.0f;
        f[14] = 0.0f;
        nv[3] = one;
        func_001FD9D8(slot, p + 0x80, m, nv, t);
    }
    *(short *)(p + EM_COL_A) = 1;
    *(short *)(p + EM_COL_B) = 1;
    *(char **)(p + EM_SUB_PTR) = p + EM_SUB_BUF;
    *(unsigned char *)(p + EM_SUB_KIND) = 6;
    *(int *)(p + EM_WORK_5EC) = 7;
    *(int *)(p + EM_WORK_5E8) = 0;
    *(int *)(p + EM_WORK_5E4) = 0;
    *(int *)(p + EM_WORK_5F0) = 0;
    *(short *)(p + EM_WORK_5F6) = 0;
    *(short *)(p + EM_TARGET) = -1;
    func_001C28A0(p);
    return 1;
}
