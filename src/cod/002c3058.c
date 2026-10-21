/* sn-2.95.3-136 matched TU. */
#include "godhand/cSceAtManager.h"

/* Take unit out of the tagged unit list that starts at link: find the link
   that points at it and make it skip to the unit's own next link. */
__attribute__((section(".text.cSceAtManager_unlinkUnit")))
void cSceAtManager_unlinkUnit(cSceAtManager *self, unsigned int *link, cSceAtUnit *unit) {
    while (*link != SCEAT_LIST_END) {
        if ((*link & SCEAT_LINK_UNIT) && (cSceAtUnit *)(*link & SCEAT_LINK_ADDR) == unit) {
            *link = unit->link;
            return;
        }
        link = (unsigned int *)(*link & SCEAT_LINK_ADDR);
    }
}
