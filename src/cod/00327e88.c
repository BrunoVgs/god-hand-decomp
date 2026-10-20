/* cygnus-2.96: sets the stream parameters between the lock/unlock trampolines. */
extern void Obj3290_Tramp_0033E678_9028(void);
extern void Obj3290_Tramp_0033E690_9040(void);

__attribute__((section(".text.func_00327E88")))
void func_00327E88(char *a0, int a1, int a2, int a3, int a4)
{
    Obj3290_Tramp_0033E678_9028();
    *(int *)(a0 + 0xC) = a3;
    *(int *)(a0 + 0x10) = a4 << 11;
    *(int *)(a0 + 0x14) = a4;
    *(int *)(a0 + 0x50) = a1;
    *(int *)(a0 + 0x54) = a2;
    *(unsigned char *)(a0 + 0x45) = 1;
    Obj3290_Tramp_0033E690_9040();
}
