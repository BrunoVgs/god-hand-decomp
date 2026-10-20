extern char D_005FEE00[];
extern void cSnd_SeCall_2CBA48(
    void *, int, int, void *, int, int, int, int);

__attribute__((section(".text.func_001BFCE8")))
void func_001BFCE8(void *self)
{
    cSnd_SeCall_2CBA48(D_005FEE00, 2, 0xA, self, 0, 0, 0, 0);
}
