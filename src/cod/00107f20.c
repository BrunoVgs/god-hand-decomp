extern int D_00747A80;
extern char D_005FEE00[];
extern int cGameObj_isClip(void *);

__attribute__((section(".text.func_00107F20")))
int func_00107F20(void *p)
{
    if (D_00747A80 < 0)
        return 1;
    return cGameObj_isClip(p) != 0;
}
