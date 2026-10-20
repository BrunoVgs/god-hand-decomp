/* func_00328F30: exact clone of func_00323000 (src/cod/002b62f8.c). */
/* cygnus-2.96 matched TU. */

extern void NoOp_33E6A8(void);
extern int NoOp_33E6B0(void);
extern void func_00335CD8(int a0);
extern void func_00335980(int a0);
extern int Obj34D8_SetGlobalEE0B8_IfField48(int a0);
extern void func_0034DD70(int a0, int a1);
extern void Obj3290_Tramp_0033E6A8_9070(int a0);
extern int func_00328F68(int a0);
extern void Obj3290_Tramp_0033E6B0_9088(void);
extern void Obj33F8_NoOp_FCA0(void);
extern int Obj33F8_NoOp_FCA8(void);
extern int Forward33B790_340AE8(void *p);
extern void Obj33F8_Tramp_0033B658_FC70(void);
extern void Obj33F8_Tramp_0033B670_FC88(void);


__attribute__((section(".text.func_00328F30")))
int func_00328F30(int a0) {
    int r;
    Obj3290_Tramp_0033E6A8_9070(a0);
    r = func_00328F68(a0);
    Obj3290_Tramp_0033E6B0_9088();
    return r;
}



