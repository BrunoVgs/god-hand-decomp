/* Batch 52: unique SN ~160–176 (scratch-only). */
#include "include_asm.h"
#include "godhand/vu0.h"

extern int func_00323000(int a0);
extern int func_00323918(int a0, int a1);
extern void *func_0031C8B8(int a0, int a1);
extern void func_003A6A20(void *msg);
extern void func_00323A70(void *p);
extern void func_00323E80(void *p, int a1, void *a2);
extern char D_0045C270[];

extern int D_00747A34;
extern char D_00754C10[];
extern int D_0041B730;
extern void *EnsureInitThenForward_2A9538_30EE08(int size, int align, void *region);
extern void func_003A52F0(void *dst, int val, int len);
extern void cPlBase(void *a0);

__attribute__((section(".text.func_0037FC28")))
void func_0037FC28(char *self)
{
    char *s1 = self;
    char *s0;
    int v0;
    int v1;

    v0 = func_00323000(0xFF);
    v1 = 3;
    s0 = s1 + 0x370;
    if (v0 != v1)
        return;
    v0 = func_00323918(0xFF, (int)*(unsigned char *)(s1 + 6));
    *(int *)(s0 + 0xF4) = v0;
    v0 = (int)func_0031C8B8(0x800, 0x40);
    *(int *)(s0 + 0xF8) = v0;
    if (v0 == 0) {
        func_003A6A20(D_0045C270);
        v0 = 1;
        *(unsigned char *)(s0 + 1) = (unsigned char)v0;
        func_00323A70(*(void **)(s0 + 0xF4));
        v0 = 0xA;
        *(unsigned char *)(s1 + 2) = (unsigned char)v0;
        return;
    }
    {
        void *a0 = *(void **)(s0 + 0xF4);
        void *a2 = (void *)v0;
        func_00323E80(a0, 1, a2);
    }
    v1 = 5;
    *(unsigned char *)(s1 + 2) = (unsigned char)v1;
}

INCLUDE_ASM("nonmatching", func_00313030);
