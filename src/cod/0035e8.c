/* Struct: CGObj35E8_t — fields +0x4..+0x70; counter (StepCounter) and indirect pointer (SetIndirect). */
#include "include_asm.h"
#include "godhand/sfxlib.h"
/* Struct: CGObj35E8_t — fields +0x4..+0x70; counter (StepCounter) and indirect pointer (SetIndirect). */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035E868 — call-chain (jal×2, complex branch)                         */
/* ════════════════════════════════════════════════════════════════════════ */
extern void *getElemInfPtr(int a0, int a1);
typedef struct Elem {
    char pad0[0x20];
    unsigned char codec;
} Elem;
extern int func_0035E9E8(unsigned int id);
extern int isEnableVidFtr(int a0, Elem *a1);

__attribute__((section(".text.func_0035E868")))
int func_0035E868(int a0, int a1, int *a2)
{
    void *s1;
    int s0;
    s0 = a1 & 0xFF;
    *a2 = -1;
    s1 = getElemInfPtr(a0, s0);
    if (s1 == 0) {
        return 0;
    }
    if (isEnableVidFtr(s0, s1) == 0) {
        return 0;
    }
    if (*(int *)((char *)a0 + 0xC) < 0xD2) {
        return 0;
    }
    *a2 = *(unsigned char *)((char *)s1 + 0x27);
    return 1;
}

/* func_0035E8F8 (0x0035E8F8): NOT carved — jump-table entries              */
/* (.L0035E920) are referenced from rodata D_00459C50; the label must      */
/* remain in the monolithic fragment to be visible to the jump-table .o.   */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035E968 — call-chain: jal E9E8 + branch + movz                       */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.isEnableAudFtr")))
int isEnableAudFtr(int id, Elem *e)
{
    int nz;
    int lt;

    if (func_0035E9E8(id) != 0xC0) return 0;
    nz = (e->codec != 0);
    lt = (e->codec < 2);
    return lt && nz;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035E9A8 — call-chain: jal E9E8 + branch + movz (checks 0xE0)         */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.isEnableVidFtr")))
int isEnableVidFtr(int id, Elem *e)
{
    int nz;
    int lt;

    if (func_0035E9E8(id) != 0xE0) return 0;
    nz = (e->codec != 0);
    lt = (e->codec < 2);
    return lt && nz;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035E9E8 — branched leaf: range checks + exact matches                 */
/*  a0 in [0xC0,0xE0) → 0xC0;  in [0xE0,0xF0) → 0xE0                     */
/*  a0 == 0xBD or 0xBF → 0xBD; else → 0                                   */
/*  NOTE: compiler generates bne+delay v0=0 in reference vs xori+movn      */
/*  here → size mismatch (0x40 vs 0x44) → keep as nonmatching asm          */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.func_0035E9E8")))
int func_0035E9E8(unsigned int id)
{
    if (id - 0xC0 < 0x20) return 0xC0;
    if (id - 0xE0 < 0x10) return 0xE0;
    if (id == 0xBD) goto bd;
    if (id != 0xBF) return 0;
bd:
    return 0xBD;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EA30 — arg-rearrange + stores + ra-save tail-call                  */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EA60 — medium leaf: counter step arithmetic                        */
/*  *(int*)(a0+0xC) = count                                                */
/*  *(int*)(a0+0x10) = step                                                */
/*  result: a0[4] += step*(count-1); a0[0x10] = -step                     */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.Obj35E8_StepCounter_EA60")))
void Obj35E8_StepCounter_EA60(char *a0)
{
    int v1 = *(int *)(a0 + 0xC);
    int v0 = *(int *)(a0 + 0x10);
    int a1 = *(int *)(a0 + 0x4);
    *(int *)(a0 + 0x10) = -v0;
    *(int *)(a0 + 0x4) = a1 + v0 * (v1 - 1);
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EA88 — large branched call-chain (jal FBD8)                        */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EB60 — branched leaf: type-dispatch via movn                       */
/*  if *(a0+4)==0x51: return 4;  if *(a0+4)==0x61: return 5               */
/*  else: return (*(a1+0x94) != 0x51) ? 5 : 4                              */
/*  NOTE: reference uses $a2 for 0x51 constant + movn; compiled uses $v1   */
/*  + xori + movz → register mismatch → keep as nonmatching asm            */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EB98 — ra-save trampoline (sd ra; ld ra; j EBB0) — nonmatching     */
/* ════════════════════════════════════════════════════════════════════════ */

/* func_0035EBB0 (0x0035EBB0): NOT carved — PERMANENT (bnel) AND            */
/* jump-table label .L0035ECC8 referenced from rodata D_00459CE0; must     */
/* remain in the monolithic fragment for label visibility.                  */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035ED08 — PERMANENT (beql): branch logic with beql instructions       */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EDA8 — ra-save + lw×3 + tail-call func_003603D8                   */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EDC8 — ra-save + lw + tail-call func_0035EDE0                     */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EDE0 — PERMANENT (.word 0x460000E4): FP init table                 */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EE98 — ra-save + lw×3 + tail-call func_0036CBC0                   */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EEB8 — ra-save + lw×3 + tail-call func_0036CC08                   */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EED8 — ra-save + lw×3 + tail-call func_0036CC40                   */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EEF8 — branched leaf: optional function-pointer call               */
/*  v0 = *(int*)(a0+0x70); if (v0) call v0(*(int*)(a0+0x38))              */
/*  NOTE: reference uses beqz, compiled uses beqzl (likely-branch)         */
/*  at offset c → different delay-slot content → keep as nonmatching asm   */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF20 — no-jr-ra stub (addiu sp+0x20 twice) — nonmatching           */
/* ════════════════════════════════════════════════════════════════════════ */

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF30 — accessor: *(a0+0x68) = a1                                  */
/* jr $ra; sw $a1, 0x68($a0)                                               */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.Obj35E8_SetField_68")))
void Obj35E8_SetField_68(char *a0, int a1)
{
    *(int *)(a0 + 0x68) = a1;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF38 — accessor: *(a0+0x6C) = a1                                  */
/* jr $ra; sw $a1, 0x6C($a0)                                               */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.Obj35E8_SetField_6C")))
void Obj35E8_SetField_6C(char *a0, int a1)
{
    *(int *)(a0 + 0x6C) = a1;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF40 — indirect accessor: ptr=*(a0+0x30); *(ptr+0x18)=a1          */
/* lw $v0, 0x30($a0); jr $ra; sw $a1, 0x18($v0)                           */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.Obj35E8_SetIndirect_30_18")))
void Obj35E8_SetIndirect_30_18(char *a0, int a1)
{
    *(int *)(*(int *)(a0 + 0x30) + 0x18) = a1;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF50 — indirect accessor: ptr=*(a0+0x30); *(ptr+0x20)=a1          */
/* lw $v0, 0x30($a0); jr $ra; sw $a1, 0x20($v0)                           */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.Obj35E8_SetIndirect_30_20")))
void Obj35E8_SetIndirect_30_20(char *a0, int a1)
{
    *(int *)(*(int *)(a0 + 0x30) + 0x20) = a1;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF60 — indirect accessor: ptr=*(a0+0x30); *(ptr+0x1C)=a1          */
/* lw $v0, 0x30($a0); jr $ra; sw $a1, 0x1C($v0)                           */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.Obj35E8_SetIndirect_30_1C")))
void Obj35E8_SetIndirect_30_1C(char *a0, int a1)
{
    *(int *)(*(int *)(a0 + 0x30) + 0x1C) = a1;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF70 — accessor: *(a0+0x70) = a1                                  */
/* jr $ra; sw $a1, 0x70($a0)                                               */
/* ════════════════════════════════════════════════════════════════════════ */
__attribute__((section(".text.Obj35E8_SetField_70")))
void Obj35E8_SetField_70(char *a0, int a1)
{
    *(int *)(a0 + 0x70) = a1;
}

/* ════════════════════════════════════════════════════════════════════════ */
/* 0x0035EF78 — large call-chain (0x258 bytes; jal×4)                       */
/* ════════════════════════════════════════════════════════════════════════ */


extern void func_0035FD98(void *a, int b, int c);
extern char D_00459C70[];
extern char D_00459ED8[];
extern char D_00459EE0[];
extern int func_0035F830(void *a, void *b);
extern void func_0035F1D0(void *a, void *b, int c, int d);
extern void func_0035F3C8(void *a, void *b, int c);
extern int func_0036CC78(int a);
extern void func_003603D8(int a, int b, void *c);
extern void func_0036CBC0(int a, int b, void *c);
extern void func_0036CC08(int a, int b, void *c);
extern void func_0036CC40(int a, int b, void *c);

__attribute__((section(".text.func_0035EA30")))
void func_0035EA30(void *self, Obj35E8Arg *b, int c, int d, int e, int f)
{
    b->unk44 = e;
    b->unk48 = f;
    func_0035FD98(b, c, d);
}

__attribute__((section(".text.func_0035EB60")))
int func_0035EB60(Obj35E8Type *a, Obj35E8Mode *b)
{
    int t = a->unk4;
    int r;

    if (t == 0x51U)
        return 4;
    if (t == 0x61)
        return 5;
    if (b->unk94 == 0x51U) {
        r = 4;
        return r;
    }
    return 5;
}

__attribute__((section(".text.func_0035EB98")))
void func_0035EB98(void *a, void *b, int mode)
{
    func_0035EBB0(a, b, mode);
}

__attribute__((section(".text.func_0035EDA8")))
void func_0035EDA8(Obj35E8 *a, Obj35E8Arg *b)
{
    func_003603D8(a->unk24, b->unk4C, a->unk38);
}

__attribute__((section(".text.func_0035EDC8")))
void func_0035EDC8(Obj35E8 *a)
{
    func_0035EDE0(a->unk38);
}

__attribute__((section(".text.func_0035EE98")))
void func_0035EE98(Obj35E8 *a, Obj35E8Arg *b)
{
    func_0036CBC0(a->unk30, b->unk4C, a->unk38);
}

__attribute__((section(".text.func_0035EEB8")))
void func_0035EEB8(Obj35E8 *a, Obj35E8Arg *b)
{
    func_0036CC08(a->unk30, b->unk4C, a->unk38);
}

__attribute__((section(".text.func_0035EED8")))
void func_0035EED8(Obj35E8 *a, Obj35E8Arg *b)
{
    func_0036CC40(a->unk30, b->unk4C, a->unk38);
}

__attribute__((section(".text.func_0035EEF8")))
void func_0035EEF8(Obj35E8 *a)
{
    void (*fn)(void *) = a->unk70;
    void *arg = a->unk38;
    if (fn) fn(arg);
}

#ifdef NON_MATCHING
/* Retail lowers this switch to a compare tree; every compiler here emits a jump table. */
__attribute__((section(".text.func_0035ED08")))
int func_0035ED08(Obj35E8 *a, int mode)
{
    int ret = 1;
    if (a->unk34 == 100) return 0;
    if (a->unk34 != mode) return ret;
    switch (mode) {
    case 0:
        break;
    case 1: case 4: case 5: case 0x15:
        ret = 0;
        break;
    case 2:
        if (func_0036CC78(a->unk30) != 1) ret = 0;
        break;
    }
    return ret;
}
#else
INCLUDE_ASM("permanent", func_0035ED08);
#endif

__attribute__((section(".text.func_0035EDE0")))
void func_0035EDE0(unsigned char *t)
{
    int i;
    for (i = 0; i < 16; i++) t[i] = 0;
    for (i = 16; i < 0xEC; i++) t[i] = (i - 16) * 0.582f;
    for (i = 0xEC; i < 0x100; i++) t[i] = 0x80;
}

__attribute__((section(".text.func_0035EA88")))
int func_0035EA88(Obj35E8Type *a)
{
    switch (a->unk4) {
    case 0x11: case 0x31: case 0x41: case 0x51: case 0x61:
    case 0x71: case 0xF1: case 0x111: case 0x1001:
        return 0;
    case 0x21: case 0x101:
        return 1;
    default:
        SFXLIB_Error(0, 0, D_00459C70);
        return 0;
    }
}

__attribute__((section(".text.func_0035EF78")))
void func_0035EF78(Obj35E8Type *a, Obj35E8Mode *b, int c)
{
    int type = a->unk4;

    if (type == 0)
        a->unk4 = func_0035F830(b, D_00459ED8);
    switch (type) {
    case 0x11:
        if (b->unk90 != 1) {
            func_0035F1D0(a, b, c, 0);
            return;
        }
        /* fallthrough */
    case 0x1001:
        func_0035EB98(a, b, 0x15);
        func_0035F1D0(a, b, c, 1);
        return;
    case 0x21:
        func_0035EB98(a, b, 1);
        func_0035F3C8(a, b, c);
        return;
    case 0x31:
        func_0035EB98(a, b, 2);
        func_0035F1D0(a, b, c, 1);
        return;
    case 0x41: case 0x51: case 0x61:
        func_0035EB98(a, b, func_0035EB60(a, b));
        func_0035F1D0(a, b, c, 1);
        return;
    case 0x101:
        func_0035F1D0(a, b, c, 0);
        return;
    case 0x71: case 0xF1: case 0x111:
    default:
        SFXLIB_Error(a, b, D_00459EE0);
        return;
    }
}
