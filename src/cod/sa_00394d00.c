/* sn-2.95.3-136: NM closer handoff. */
#include "godhand/regTbl.h"
/* sn-2.95.3-136: func_00394D00, split from src/cod/batch31_nm.c by the NM closer. */

__attribute__((section(".text.func_00394D00")))
int func_00394D00(int key)
{
    unsigned int i;

    for (i = 0; i < D_003F5520.count; i++) {
        if (D_003F5520.ent[i].key == key) {
            D_003F5520.ent[i].a = 0;
            D_003F5520.ent[i].key = 0;
            D_003F5520.ent[i].check = 0;
            return i;
        }
    }
    return -1;
}
