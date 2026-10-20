extern char D_005FEE00[];
extern int func_0032DCD0(int handle, int arg);

__attribute__((section(".text.func_00374928")))
int func_00374928(int *p, int arg)
{
    if (*p == 0)
        return 0;
    return func_0032DCD0(*p, arg);
}
