#include "godhand/cScenario.h"
extern int D_003C23A4;
extern int cMessage_ckMessage(int, int);

__attribute__((section(".text.cScenario_isMessOn")))
int cScenario_isMessOn(cScenario *self)
{
    if (self->messNo == 0xFFFF)
        return 0;
    return cMessage_ckMessage(D_003C23A4, self->messNo);
}
