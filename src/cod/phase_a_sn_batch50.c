/* Batch 50: unique SN ~176–184 (scratch-only). */

extern void cIDBase_initialize(void *p, int a1, int a2);
extern void func_00144C90(void *self);
extern unsigned short D_003BD70C;
extern int func_002E0DE8(int a0, int a1, int a2, void *msg);
extern void *func_003750E0(void *p);
extern char D_0045BD90[];
extern char D_0045BDA0[];
extern char D_0045BDA8[];
extern char D_0045BDB8[];

__attribute__((section(".text.func_0037B338")))
void func_0037B338(char *self)
{
    char *s0 = self;
    void *a0;
    int v0;

    func_002E0DE8(3, 4, 8, D_0045BD90);
    a0 = *(void **)(s0 + 0xC);
    if (a0 == 0) {
        func_002E0DE8(0xC, 4, 0xF, D_0045BDA0);
        return;
    }
    s0 = (char *)func_003750E0(a0);
    v0 = (int)s0 & 1;
    if (s0 == 0) {
        func_002E0DE8(0xC, 4, 0xF, D_0045BDA0);
        return;
    }
    if (v0)
        func_002E0DE8(0xC, 4, 0xD, D_0045BDA8);
    if (((int)s0) & 2)
        func_002E0DE8(0xC, 4, 0xC, D_0045BDB8);
}
