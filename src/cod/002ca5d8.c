/* sn-2.95.3-136 matched TU. */

#include "godhand/cSnd.h"

extern void cSndSeVoice_Update(cSndSeVoice *voice);
extern void cSndSeVoice_Stop(cSndSeVoice *voice);

#define CSND_F_SE_PENDING  0x04000000   /* bit of flagsAC / flagsB0: sound effects wait to be flushed */
#define CSND_VOICE_STOP_BIT 2           /* voice flag bit that marks it for stopping */

/* Clears the pending bit, steps every voice, and if the bit came back stops the voices flagged for it. */
__attribute__((section(".text.func_002CA5D8")))
void func_002CA5D8(cSnd *self) {
    cSndSeVoice *v;

    self->flagsB0 = self->flagsB0 & ~CSND_F_SE_PENDING;
    self->flagsAC = self->flagsAC & ~CSND_F_SE_PENDING;
    for (v = self->voiceHead; v != 0; v = v->next) {
        cSndSeVoice_Update(v);
    }
    if ((self->flagsAC & CSND_F_SE_PENDING) != 0) {
        for (v = self->voiceHead; v != 0; v = v->next) {
            unsigned long flags = v->flags;
            unsigned long bit = (flags >> CSND_VOICE_STOP_BIT) & 1;
            if (bit) {
                cSndSeVoice_Stop(v);
            }
        }
    }
}
