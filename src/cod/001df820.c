extern char D_005FEE00[];
extern void func_001DD068(void *);
extern void func_001DEC70(void *);
extern void CustomIDWork_SetMoveOffsetPosXSin(
    void *, int, unsigned short);
extern void CustomIDWork_ResetMoveOffsetPos(void *);

__attribute__((section(".text.func_001DF820")))
void func_001DF820(char *self, int enabled)
{
    if (enabled)
        CustomIDWork_SetMoveOffsetPosXSin(self + 0x440, 4, 8);
    else
        CustomIDWork_ResetMoveOffsetPos(self + 0x440);
}

__attribute__((section(".text.func_001DF858")))
void *func_001DF858(char *p)
{
    func_001DD068(p);
    func_001DEC70(p + 0x25B0);
    *(int *)(p + 0x2E50) = 0;
    return p;
}
