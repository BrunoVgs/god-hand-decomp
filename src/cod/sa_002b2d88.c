/* sn-2.95.3-136: cutscene frame-range command and SE voice switch (0x2B2D88..). */

#include "godhand/cutCmd.h"

extern unsigned int D_00747A84;
extern char D_00586AF0[];
extern char D_005FEE00[];
extern char D_0044B1E0[];
extern unsigned int cEvent_getCutNo();
extern void *SearchData(void *name, void *table, int which);
extern void cSndSeVoice_CheckEnd(void *snd, int handle);
extern int cSnd_ReserveSeSlot(void *snd, int id);

#define SYSFLAG_EVENT_RUNNING  0x20000000

__attribute__((section(".text.func_002B2E80")))
void func_002B2E80(SeCmd *self)
{
    void *se;

    if (self->owner == 0) {
        se = 0;
    } else {
        se = SearchData(self->owner->seName, D_0044B1E0, 0);
    }
    if (se != self->se) {
        if (self->se != 0) {
            cSndSeVoice_CheckEnd(D_005FEE00, self->voice);
        }
        if (se != 0) {
            self->voice = cSnd_ReserveSeSlot(D_005FEE00, (int)se);
        }
        self->se = se;
    }
    if (self->owner != 0) {
        self->wait = 0xFFFF;
    } else {
        self->wait = 0xFFFF;
    }
    self->prev = self->next;
    self->cur = self->rec;
    self->count++;
}
