/* sn-2.95.3-136. */
extern int func_00373A50(char *self);
extern int func_00373B20(char *self);

__attribute__((section(".text.func_00373A78")))
int func_00373A78(char *self)
{
    int i;

    if (func_00373A50(self) == 0) {
        return 1;
    }
    if (func_00373B20(self) == 1) {
        for (i = 0; i < *(int *)(self + 0x58); i++) {
            if (((float *)(self + 0x1C))[i] > 0.0f) {
                return 0;
            }
        }
        return 1;
    }
    if (*(float *)(self + 0x18) > 0.0f) {
        return 0;
    }
    return 1;
}
