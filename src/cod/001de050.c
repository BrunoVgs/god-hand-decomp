extern void CustomIDWork_SetMoveOffsetPosXSin(
    void *, int, unsigned short);
extern void CustomIDWork_ResetMoveOffsetPos(void *);

__attribute__((section(".text.func_001DE050")))
void func_001DE050(char *self, int enabled)
{
    if (enabled)
        CustomIDWork_SetMoveOffsetPosXSin(self + 0x162C, 4, 8);
    else
        CustomIDWork_ResetMoveOffsetPos(self + 0x162C);
}
