extern char D_005FEE00[];
extern void cDamageUnit_SetDamageCollActive(void *, int);

__attribute__((section(".text.func_0018A3B8")))
void func_0018A3B8(char *self, int index)
{
    void *unit;
    self += index << 2;
    unit = *(void **)(self + 0x600);
    if (unit != 0)
        cDamageUnit_SetDamageCollActive(unit, 0);
}
