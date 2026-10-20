/* sn-2.95.3-136: is the element registered with kind 2 or 4? Stale entries of other kinds are deactivated
 * and the lookup falls back to func_003943D0. */
#include "godhand/regTbl.h"
extern int func_003A5678(int a0, int a1);
extern int func_003943D0(RegEnt *a0);

__attribute__((section(".text.func_003944E8")))
int func_003944E8(RegEnt *a0) {
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
                    if (elem->active != 0 && elem->id == a0->id &&
                        func_003A5678(elem->name, a0->name) == 0) {
                        if (elem->kind == 2 || elem->kind == 4) {
                            return 1;
                        }
                        elem->active = 0;
                        goto fallback;
                    }
                    elem++;
                } while (--cnt != 0);
            }
            node = node->next;
        } while (node != 0);
    }
fallback:
    return func_003943D0(a0);
}
