/* sn-2.95.3-136: func_002B33D8, set flag bit 1 at +0x14 unless bit 1 is set, bit 2 is clear and the lookup
 * for the id at *0x8C has bit 0 clear; then run the step. The flag tests need the long widening (lw + dsrl). */
#include "godhand/cMessDrawFontCode.h"
extern unsigned int func_002A4C00(void *table, unsigned short id);
extern void func_002B3460(char *self);

__attribute__((section(".text.func_002B33D8")))
void func_002B33D8(char *self)
{
    unsigned int r;
    long t;

    if (*(int *)(self + 0x1C) == 0)
        return;
    r = func_002A4C00(D_003C2380, **(unsigned short **)(self + 0x8C));
    t = *(int *)(self + 0x14);
    if ((((unsigned long)t >> 1) & 1UL) != 1UL || (((unsigned long)t >> 2) & 1UL) == 1UL || (r & 1)) {
        *(int *)(self + 0x14) |= 2;
        return;
    }
    func_002B3460(self);
}
