extern char D_005FEE00[];
extern void KillEffect(void *, int, int);
extern void cOmBase_dieCommon(void *);

__attribute__((section(".text.func_001B8448")))
void func_001B8448(void *p)
{
    KillEffect(p, 0, 2);
    cOmBase_dieCommon(p);
}
