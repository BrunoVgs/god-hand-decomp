/* sn-2.95.3-136 matched TU. */

#include "godhand/cMessage.h"
#include "godhand/cSceAtUnit.h"
#include "godhand/cOm4f.h"

extern void cMessage_closeMessNo8(cMessage *self, int kind);
extern void ActorMove_resetMotion(cMessageWin *win, int messNo, int kind, void *owner);
extern void cArea_AreaGetCenterPos(void *area, float *pos);
extern unsigned char cOm4f_isOpen(cOm4f *self);
extern int GetField_774_1BDD90(void *door);
extern int GetField_775_1BDD98(void *door);
extern void cOmDoor2_setOpen(void *door);
extern void cOmDoor2_setClose(void *door);

/* Open a window for message messNo owned by `owner`; returns its work id or CMESSAGE_NONE. */
__attribute__((section(".text.cMessage_create")))
unsigned int cMessage_create(cMessage *self, unsigned int messNo, void *owner, unsigned char kind, short param)
{
    cMessageWin *win;
    unsigned int workId;
    cMessage_closeMessNo8(self, kind);
    win = Queue_insertSorted(self, param);
    if (win != 0) {
        ActorMove_resetMotion(win, messNo & 0xFFFF, kind, owner);
        workId = win->workId;
    } else {
        workId = CMESSAGE_NONE;
    }
    return workId;
}

/* Write the area centre into pos, lifted by 0.4 in y; does nothing while disabled. */
__attribute__((section(".text.cSceAtUnit_getCenterPos")))
void cSceAtUnit_getCenterPos(cSceAtUnit *self, float *pos)
{
    if (((self->flags ^ 1) & 1) == 0) {
        cArea_AreaGetCenterPos(self->area, pos);
        pos[1] += 0.4f;
    }
}

/* Make the partner door follow this one: open it when we stand open, close it when we are shut. */
__attribute__((section(".text.cOm4f_syncDoor")))
void cOm4f_syncDoor(cOm4f *self)
{
    if (self->door == 0) return;
    if (cOm4f_isOpen(self) == 1) {
        if (GetField_774_1BDD90(self->door) == 0 && GetField_775_1BDD98(self->door) == 0) {
            cOmDoor2_setOpen(self->door);
        }
    }
    if (cOm4f_isOpen(self) == 0) {
        if (GetField_774_1BDD90(self->door) == 1 && GetField_775_1BDD98(self->door) == 0) {
            cOmDoor2_setClose(self->door);
        }
    }
}
