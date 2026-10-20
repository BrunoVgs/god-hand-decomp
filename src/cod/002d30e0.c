extern char D_005FEE00[];
extern int ReqQueue_push(int, int, int, int, int);

__attribute__((section(".text.func_002D30E0")))
int func_002D30E0(int a, int b, int c, int d)
{
    return ReqQueue_push(a, 1, b, c, d);
}
