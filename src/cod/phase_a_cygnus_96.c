/* cygnus-2.96 matched 96-byte Phase A functions. */

extern void Forward33B658_3403C8(void);
extern void func_003407A0(void *, int, void *, void *);
extern void Forward33B670_3403E0(void);
extern void Forward349308_349238(void);
extern int D_00457B90;
extern void func_00348A08(int, void *, int, void *);
extern void func_00349250(void);
extern int D_00457BA8;
extern void func_00348AC8(void *, int, void *);
extern void func_003492A0(void);
extern int D_00457BC0;
extern void func_00348A70(void *, int, void *);
extern void func_00348B20(void);
extern void Thunk_func_0033B658(void *);
extern int func_00355130(int, int, int);
extern void Thunk_func_0033B670(void *);

__attribute__((section(".text.func_00340740")))
void func_00340740(void *object, short index, void *third, void *fourth)
{
    Forward33B658_3403C8();
    func_003407A0(object, index, third, fourth);
    Forward33B670_3403E0();
}

__attribute__((section(".text.func_00345490")))
void func_00345490(void)
{
    func_00348A08(2, Forward349308_349238, 0, &D_00457B90);
    func_00348AC8(func_00349250, 0, &D_00457BA8);
    func_00348A70(func_003492A0, 0, &D_00457BC0);
    func_00348B20();
}

__attribute__((section(".text.func_003550D0")))
int func_003550D0(int first, int second, int third)
{
    char guard[16];
    int result;
    Thunk_func_0033B658(guard);
    result = func_00355130(first, second, third);
    Thunk_func_0033B670(guard);
    return result;
}
