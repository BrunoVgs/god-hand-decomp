/* cygnus-2.96 */

extern void *func_003A52F0(void *, int, int);
extern void Obj33F8_Tramp_0033B658_FC70(void);
extern void Obj33F8_Tramp_0033B670_FC88(void);
extern int D_003D1E68;
extern char D_003D1E70[];

__attribute__((section(".text.func_0032F288")))
void func_0032F288(void)
{
    Obj33F8_Tramp_0033B658_FC70();
    if (--D_003D1E68 == 0)
        func_003A52F0(D_003D1E70, 0, 0x6590);
    Obj33F8_Tramp_0033B670_FC88();
}
