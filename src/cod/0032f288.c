/* Cygnus helper requiring the compiler's original block order. */

extern void func_003A52F0(void *, int, int);
extern int Obj33F8_Tramp_0033B658_FC70(void);
extern int Obj33F8_Tramp_0033B670_FC88(void);
extern int D_003D1E68;
extern char D_003D1E70[];

__attribute__((section(".text.func_0032F288")))
int func_0032F288(void)
{
    Obj33F8_Tramp_0033B658_FC70();
    if (--D_003D1E68 == 0)
        func_003A52F0(D_003D1E70, 0, 0x6590);
    return Obj33F8_Tramp_0033B670_FC88();
}
