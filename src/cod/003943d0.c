#include "godhand/regTbl.h"
extern int func_003A5678(int a0, int a1);

extern int func_00394290(int a0, int a1, int idx, int a3);

__attribute__((section(".text.func_003943D0")))
int func_003943D0(RegEnt *a0) {
    RegTbl *node;
    RegEnt *elem;
    int cnt;
    int name;
    int val;
    unsigned short id;

    a0->active = 1;
    id = a0->id;
    val = a0->value;
    node = D_003F852C;
    name = a0->name;
    if (node != 0) {
        do {
            cnt = node->count;
            elem = node->ents;
            if (cnt != 0) {
                do {
                    if (elem->id == id && func_003A5678(elem->name, name) == 0 &&
                        (elem->kind == 1 || elem->kind == 3)) {
                        if (func_00394290(node->handleA, node->handleB, elem - node->ents, val) == 0)
                            return 0;
                        break;
                    }
                    elem++;
                } while (--cnt != 0);
            }
            node = node->next;
        } while (node != 0);
    }
    return 1;
}
