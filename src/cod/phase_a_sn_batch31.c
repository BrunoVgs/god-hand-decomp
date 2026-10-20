/* Batch 31: unique SN matches + near-miss conversions. */
#include "include_asm.h"
#include "godhand/vu0.h"

extern void InitFields_1B6E90(void *object);
extern void cIDBase_release(void *p);
extern void cHeap_free(void *heap, void *block);
extern void func_002A9528(void *heap);
extern void func_002C53A8(void *p);
extern int D_00429B88;
extern int D_004298B0;
extern int D_00754C10;
extern int D_00754C20;
extern int D_00754C30;
extern int D_00754C38;
extern int D_00754C50;
extern int D_00754C58;
extern char *D_003C2384;
extern int D_00747A84[];

INCLUDE_ASM("nonmatching", func_003182D8);

INCLUDE_ASM("nonmatching", func_002BF420);
