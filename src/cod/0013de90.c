/* sn-2.95.3-136 matched TU. */

#include "godhand/CustomIDWork.h"

#define IDBANK_WORK_NUM 5

/* An ID display holder: the vtable pointer at 0x80 and five CustomIDWork
 * elements from 0x120. */
typedef struct IdBank {
    char unk000[0x80];
    int *vt;                            /* 0x80 */
    char unk84[0x9C];
    CustomIDWork work[IDBANK_WORK_NUM]; /* 0x120 */
} IdBank;

extern int D_0041DCC8[];                /* vtable of the base class */
extern void CustomIDWork__dtor(CustomIDWork *work, int flags);
extern void __builtin_delete(void *p);

/* Destructor: destroy the five elements last to first, restore the base
 * vtable and free the object when bit 0 of flags is set. */
__attribute__((section(".text.IdBank_dtor")))
void IdBank_dtor(IdBank *self, int flags)
{
    CustomIDWork *p;

    if (self->work != 0) {
        p = self->work + IDBANK_WORK_NUM;
        if (self->work != p) {
            do {
                p--;
                CustomIDWork__dtor(p, 0);
            } while (self->work != p);
        }
    }
    self->vt = D_0041DCC8;
    if (flags & 1)
        __builtin_delete(self);
}
