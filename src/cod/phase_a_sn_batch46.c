/* Batch 46: unique SN ~156–172 (scratch-only). */

extern void func_003A6C58(void *dst, void *src, unsigned char a2, unsigned char a3, unsigned char t0);
extern int cDvd_ReadAllocSized(void *dvd, void *path, void *out, void *heap, int t0, void *t1, int t2, int t3);
extern void cDvd_CheckWaitFrame(void *dvd, int frame);
extern void cDamageUnit_SetDamageCollActive(void *self, int active);
extern char D_00450EC0[];
extern char D_00583F20[];
extern char D_007474A0[];
extern char D_00754220[];
extern int D_007558A0[];

__attribute__((section(".text.func_0031CC48")))
void func_0031CC48(void)
{
    char buf[0x40];
    int sp40;
    char *s1;
    char *s0;
    unsigned char a2;
    int v0;

    s1 = D_007474A0;
    a2 = (unsigned char)s1[0x5B1];
    func_003A6C58(buf, D_00450EC0, a2, a2, (unsigned char)s1[0x5B0]);
    s0 = D_00583F20;
    v0 = cDvd_ReadAllocSized(s0, buf, s1 + 0x5AC, D_00754220, 0, &sp40, 0, 0);
    cDvd_CheckWaitFrame(s0, v0);
    D_007558A0[0] = *(int *)(s1 + 0x5AC);
    D_007558A0[1] = sp40;
}
