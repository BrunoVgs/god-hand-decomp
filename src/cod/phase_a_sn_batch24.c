/* Batch 24: SN exact clone pairs (232–252). */
#include "godhand/vu0.h"

extern void cOmBase_setMeshDispFromLayer(void *self, int layer, int on);
extern int SetEffect(int a0, int a1, void *a2, int a3, int t0, unsigned t1);
extern void cSnd_SeCall_2CBA48(void *a0, int a1, int a2, void *a3, int t0,
                              int t1, int t2, int t3);
extern char D_005FEE00[];

extern void StoreVecFromFieldB0_2B6160(void *dst, void *self);
extern int ChkLine(void *a0, void *a1, void *a2, void *a3, int a4, int a5,
                   int a6, int a7, int a8, int a9, int a10, int a11, int a12);
extern void func_002E28F0(void *self, float f12);
extern void func_002E6B88(void *self, float f12);

/* ChkLine stack args occupy sp+0..0x2F; vectors at sp+0x30..0x7F. */
#define SP_BASE(f, ofs) ((char *)(f) - (ofs))

extern int D_00741940[];
extern int D_00741960[];
extern int D_00741980[];
extern unsigned char D_0071B940[];
extern int D_0071B7C0[];
extern int D_0071B840[];
extern int D_0071B8C0[];
extern unsigned char D_0061B7C0[];
extern void func_00302918(void *p);
extern void UpdateObjByIndexedOp_2FBE50(void *p);

__attribute__((section(".text.KillEventEmitter")))
void KillEventEmitter(void)
{
    int i;
    unsigned int mask;
    int w;
    char *p;
    unsigned int top;
    int skip;

    for (i = 0, top = 0x80000000u, skip = 0xD7; i < 0x100; i++) {
        w = (unsigned int)i >> 5;
        mask = top >> (i & 0x1F);
        if ((D_00741940[w] & mask) == 0)
            goto next;
        if ((D_00741960[w] & mask) != 0)
            goto next;
        if ((D_00741980[w] & mask) != 0)
            goto next;
        p = (char *)D_0071B940 + i * 0x260;
        if ((*(int *)(p + 0x118) & 2) == 0)
            goto next;
        if (*(short *)(p + 0x18C) == skip)
            goto next;
        func_00302918(p);
next:
        ;
    }
}

extern void Obj0000_Set_Fields_68_6C_From_D_007474A0_1615D0(void *self);
extern int func_00161500(void *self, void *tbl);
extern void cIDManager_setIDData(void *mgr, int id, int data);
extern void cIDBase_initialize(void *self, int id, int mode);
extern void cIDBase_resetAnim(void *self);
extern void cIDBase_setPackedMessData(void *self, int id, int mode);
extern void *cIDBase_getIDWork(void *self, int idx);
extern int *D_003C2384;
extern char D_0041FA90[];
extern char D_0041FBA0[];

__attribute__((section(".text.func_00300D20")))
void func_00300D20(int type, unsigned int id)
{
    int i;
    unsigned int mask;
    int w;
    char *p;

    for (i = 0; i < 0x100; i++) {
        w = (unsigned int)i >> 5;
        mask = 0x80000000u >> (i & 0x1F);
        if ((D_00741940[w] & mask) == 0)
            goto next;
        if ((D_00741960[w] & mask) != 0)
            goto next;
        if ((D_00741980[w] & mask) != 0)
            goto next;
        p = (char *)D_0071B940 + i * 0x260;
        if (*(short *)(p + 0x18C) != type)
            goto next;
        if (*(unsigned short *)(p + 0x18E) != id)
            goto next;
        func_00302918(p);
next:
        ;
    }
}
