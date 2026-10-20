/* Batch 27: unique SN bodies, smallest first. Matched only. */

extern void StoreSoundEntry_3749D8(int index, void *slot);
extern int SetEffect(int a0, int a1, void *a2, int a3, int t0, unsigned t1);
extern void *func_003A5148(void *d, const void *s, unsigned int n);

__attribute__((section(".text.func_0037B768")))
void func_0037B768(char *self)
{
    int index = self[0x27];
    short *slot = (short *)(self + 0x16C + (index << 5));

    *slot = 0;
    StoreSoundEntry_3749D8(self[0x27], slot);
}

__attribute__((section(".text.func_0012C708")))
void func_0012C708(char *self)
{
    *(int *)(self + 0x5FC) = 0x258;
    SetEffect(0, 0x4E, self, 0, 5, 0xFFFFFFFFU);
}

__attribute__((section(".text.func_001451A0")))
void func_001451A0(char *self, void *src)
{
    func_003A5148(self + 0x3FA, src, (unsigned int)*(short *)(self + 0x3B2));
    *(unsigned int *)(self + 0x90) |= 0x40000000U;
}
