/* sn-2.95.3-136. */
extern int func_00373A50(char *self);
extern int func_00373B20(char *self);
extern void func_00374720(char *self, float f, float g, int a1);
extern void func_003740C8(char *self, float f, float g);

__attribute__((section(".text.func_003735E0")))
void func_003735E0(char *self, int a1, float f, float g)
{
    if (func_00373A50(self) == 0) {
        return;
    }
    if (f < 0.001f) {
        f = 0.0f;
    }
    if (func_00373B20(self) == 1) {
        func_00374720(self, f, g, a1);
    } else {
        func_003740C8(self, f, g);
    }
}
