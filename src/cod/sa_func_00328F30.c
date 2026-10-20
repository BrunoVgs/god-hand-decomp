/* func_00328F30: exact clone of func_00323000 (src/cod/002b62f8.c). */
/* cygnus-2.96 matched TU. */

extern void Obj3290_Tramp_0033E6A8_9070(int a0);
extern int func_00328F68(int a0);
extern void Obj3290_Tramp_0033E6B0_9088(void);

__attribute__((section(".text.func_00328F30")))
int func_00328F30(int a0) {
    int r;
    Obj3290_Tramp_0033E6A8_9070(a0);
    r = func_00328F68(a0);
    Obj3290_Tramp_0033E6B0_9088();
    return r;
}

