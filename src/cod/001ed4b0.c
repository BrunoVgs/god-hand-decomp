extern void CustomIDWork_SetMoveOffsetPosXSin(
    void *, int, unsigned short);
extern void CustomIDWork_ResetMoveOffsetPos(void *);

__attribute__((section(".text.func_001ED4B0")))
void func_001ED4B0(char *self, int enabled)
{
    if (enabled)
        CustomIDWork_SetMoveOffsetPosXSin(self + 0x11D0, 3, 0x10);
    else
        CustomIDWork_ResetMoveOffsetPos(self + 0x11D0);
}
