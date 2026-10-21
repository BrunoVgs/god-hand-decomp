extern void Thunk_func_0033B658(void *);
extern int func_00355130(int, int, int);
extern void Thunk_func_0033B670(void *);

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
