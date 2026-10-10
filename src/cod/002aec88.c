#include "godhand/cMessage.h"
extern cMessageWin *cMessage_releaseWin(cMessage *self, cMessageWin *win);
/* Delete every window; cMessage_releaseWin returns the next one. */
__attribute__((section(".text.cMessage_deleteAll")))
void cMessage_deleteAll(cMessage *self) {
    cMessageWin *win = self->head;
    while (win) {
        win = cMessage_releaseWin(self, win);
    }
}
