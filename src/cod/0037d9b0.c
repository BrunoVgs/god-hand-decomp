/* sn-2.95.3-136 matched TU. */
#include "godhand/SndEntry.h"

extern SndEvent D_0076CF20[SND_EVENT_NUM];   /* event table */

/* Apply request req to every active event whose group bits meet mask. */
__attribute__((section(".text.SndEvent_requestByGroup")))
void SndEvent_requestByGroup(unsigned char mask, unsigned short req) {
    SndEvent *e;
    int i;

    for (i = 0; i < SND_EVENT_NUM; i++) {
        e = &D_0076CF20[i];
        if (e->active != 0 && (e->group & mask)) {
            switch (req) {
            case SND_EVENT_REQ_1:
                e->flags |= SND_EVENT_BITS_1;
                break;
            case SND_EVENT_REQ_2:
                e->flags |= SND_EVENT_BITS_2;
                break;
            }
        }
    }
}
