/* cygnus-2.96 (drop-reorder), CRI ADX: stores a per-channel value and forwards base + value; error trap on NULL or channel > 32. */
extern void Obj33F8_Tramp_0033F130_FCB0(int);
extern int ForwardField3ByOffset_32ED48(int *a0, int a1, int a2);
extern char D_00452FB0[];
extern char D_00452FD8[];

__attribute__((section(".text.func_0032ECD8")))
void func_0032ECD8(int *a0, int ch, int v) {
    if (a0 == 0) {
        Obj33F8_Tramp_0033F130_FCB0((int)D_00452FB0);
        return;
    }
    if (ch > 32) {
        Obj33F8_Tramp_0033F130_FCB0((int)D_00452FD8);
        return;
    }
    a0[0x1EC / 4 + ch] = v;
    ForwardField3ByOffset_32ED48(a0, ch, a0[0x1E8 / 4] + v);
}
