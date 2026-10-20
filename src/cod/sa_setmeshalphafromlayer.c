/* sn-2.95.3-136: NM closer handoff. */
/* halt demote cOmBase_setMeshAlphaFromLayer */
#include "godhand/cModel.h"

extern cModelNode *cModel_getMeshPtr(cModel *self, int idx);

__attribute__((section(".text.cOmBase_setMeshAlphaFromLayer")))
void cOmBase_setMeshAlphaFromLayer(cModel *self, int layer, float alpha)
{
    cModelNode *node;

    node = cModel_getMeshPtr(self, 0);
    if (node != 0) {
        do {
            if (node->layer == layer) {
                node->alpha = alpha;
            }
            node = node->next;
            __asm__ __volatile__("nop");
        } while (node != 0);
    }
}

