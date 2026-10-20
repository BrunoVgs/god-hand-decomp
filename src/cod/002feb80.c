extern char D_005FEE00[];
extern void UpdateObjByIndexedOp_2FBE50(void *, int, int);

__attribute__((section(".text.func_002FEB80")))
void func_002FEB80(int *p, int a, int b)
{
    if (a == p[0x42] && b == p[0x43])
        UpdateObjByIndexedOp_2FBE50(p, a, b);
}
