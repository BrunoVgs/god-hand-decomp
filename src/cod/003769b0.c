/* sn-2.95.3-136 matched TU. */
#include "godhand/SndEntry.h"

extern SndVoice D_0076F050[];   /* voice table, SND_VOICE_NUM entries */

/* Return the first active voice with the given id (0 = any id), skipping
   voices flagged SND_VOICE_FLAG_SKIP, or 0 when there is none. */
__attribute__((section(".text.SndVoice_find")))
SndVoice *SndVoice_find(int id) {
    SndVoice *v = D_0076F050;
    int i;

    for (i = 0; i < SND_VOICE_NUM; i++, v++) {
        if (v->active != 0 && !(v->flags & SND_VOICE_FLAG_SKIP)) {
            if (id == 0) {
                return v;
            }
            if (v->id == id) {
                return v;
            }
        }
    }
    return 0;
}
