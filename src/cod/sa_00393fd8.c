/* sn-2.95.3-136: look up an entry by name and id across the registered tables; 0 if absent. */
#include "godhand/regTbl.h"
extern int func_003A5678(int a0, int a1);

__attribute__((section(".text.func_00393FD8")))
int func_00393FD8(int name, unsigned short id) {
    RegTbl *node;
    RegEnt *elem;
    int cnt;
    node = D_003F852C;
    if (node != 0) {
        do {
            cnt = node->count;
            elem = node->ents;
            if (cnt != 0) {
                do {
                    if (elem->active != 0 && elem->id == id &&
                        func_003A5678(elem->name, name) == 0) {
                        return elem->value;
                    }
                    elem++;
                } while (--cnt != 0);
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}
