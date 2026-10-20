extern int D_00747A80;
extern char D_005FEE00[];
extern int IsTargetVisible_14B470(void *);

__attribute__((section(".text.func_001020F0")))
int func_001020F0(void *p)
{
    if (D_00747A80 < 0)
        return 1;
    return IsTargetVisible_14B470(p) != 0;
}
