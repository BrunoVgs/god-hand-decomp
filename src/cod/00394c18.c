#include "godhand/regTbl.h"

__attribute__((section(".text.func_00394C18")))
int func_00394C18(int a, int b)
{
    unsigned int i;

    for (i = 0; i < D_003F5520.count; i++) {
        if (D_003F5520.ent[i].key == 0) {
            D_003F5520.ent[i].a = a;
            D_003F5520.ent[i].key = b;
            D_003F5520.ent[i].check = a ^ b ^ 0x31415926;
            return i;
        }
    }
    if (D_003F5520.count == 0x400) {
        return -1;
    }
    i = D_003F5520.count++;
    D_003F5520.ent[i].a = a;
    D_003F5520.ent[i].key = b;
    D_003F5520.ent[i].check = a ^ b ^ 0x31415926;
    D_003F5520.check = D_003F5520.count ^ 0x31415926;
    return i;
}
