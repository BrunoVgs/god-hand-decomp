/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"
#include "godhand/vu0.h"

extern void Esp_killByGroupNumber(int a0);
extern void func_00300AE8(int a0, int a1);
extern void func_002FBB78(int a0, int a1, int a2, int a3);

/* sn-2.95.3-136 */



#define COMBASE_F0_BIT2   0x04          /* flags0 bit 2 */

/* Start the knock step: aim the knock vector from the anchor body at the object, set mode 2 step 0, and flag the object active. */
__attribute__((section(".text.cOmBase_startKnockStepL")))
void cOmBase_startKnockStepL(cOmBase *self)
{
    cVec frame[2] __attribute__((aligned(16)));
    unsigned int f = self->flags0;
    long wide = f;
    long gone = (wide >> 1) & 1;
    if (gone) {
        return;
    }
    VU0_ZERO_VSUB_XYZ_MEM(frame, 0x10, self->pos, &self->posA);
    do { VU0_LQC2(4, &frame[1], 0); } while (0);
    VU0_SQC2(4, frame, 0);
    cVec_copy3(&self->knock, &frame[0]);
    self->mode = 2;
    self->phase = 0;
    self->step = 0;
    self->stepArg = 0;
    self->flags0 = (self->flags0 | COMBASE_F0_ACTIVE) & ~COMBASE_F0_BIT2;
}

/* sn-2.95.3-136 */



#define COMBASE_F0_BIT2   0x04          /* flags0 bit 2 */

/* Start the knock step: aim the knock vector from the anchor body at the object, set mode 2 step 0, and flag the object active. */
__attribute__((section(".text.cOmBase_startKnockStepM")))
void cOmBase_startKnockStepM(cOmBase *self)
{
    cVec frame[2] __attribute__((aligned(16)));
    unsigned int f = self->flags0;
    long wide = f;
    long gone = (wide >> 1) & 1;
    if (gone) {
        return;
    }
    VU0_ZERO_VSUB_XYZ_MEM(frame, 0x10, self->pos, &self->posA);
    do { VU0_LQC2(4, &frame[1], 0); } while (0);
    VU0_SQC2(4, frame, 0);
    cVec_copy3(&self->knock, &frame[0]);
    self->mode = 2;
    self->phase = 0;
    self->step = 0;
    self->stepArg = 0;
    self->flags0 = (self->flags0 | COMBASE_F0_ACTIVE) & ~COMBASE_F0_BIT2;
}

/* sn-2.95.3-136 */



#define COMBASE_F0_BIT2   0x04          /* flags0 bit 2 */

/* Start the knock step: aim the knock vector from the anchor body at the object, set mode 2 step 0, and flag the object active. */
__attribute__((section(".text.cOmBase_startKnockStepN")))
void cOmBase_startKnockStepN(cOmBase *self)
{
    cVec frame[2] __attribute__((aligned(16)));
    unsigned int f = self->flags0;
    long wide = f;
    long gone = (wide >> 1) & 1;
    if (gone) {
        return;
    }
    VU0_ZERO_VSUB_XYZ_MEM(frame, 0x10, self->pos, &self->posA);
    do { VU0_LQC2(4, &frame[1], 0); } while (0);
    VU0_SQC2(4, frame, 0);
    cVec_copy3(&self->knock, &frame[0]);
    self->mode = 2;
    self->phase = 0;
    self->step = 0;
    self->stepArg = 0;
    self->flags0 = (self->flags0 | COMBASE_F0_ACTIVE) & ~COMBASE_F0_BIT2;
}

/* sn-2.95.3-136 */



#define COMBASE_F0_BIT2   0x04          /* flags0 bit 2 */

/* Start the knock step: aim the knock vector from the anchor body at the object, set mode 2 step 0, and flag the object active. */
__attribute__((section(".text.cOmBase_startKnockStepO")))
void cOmBase_startKnockStepO(cOmBase *self)
{
    cVec frame[2] __attribute__((aligned(16)));
    unsigned int f = self->flags0;
    long wide = f;
    long gone = (wide >> 1) & 1;
    if (gone) {
        return;
    }
    VU0_ZERO_VSUB_XYZ_MEM(frame, 0x10, self->pos, &self->posA);
    do { VU0_LQC2(4, &frame[1], 0); } while (0);
    VU0_SQC2(4, frame, 0);
    cVec_copy3(&self->knock, &frame[0]);
    self->mode = 2;
    self->phase = 0;
    self->step = 0;
    self->stepArg = 0;
    self->flags0 = (self->flags0 | COMBASE_F0_ACTIVE) & ~COMBASE_F0_BIT2;
}

/* sn-2.95.3-136 */



/* Remove an effect from one or both of its lists: mode 0 the second list, 1 the first, 2 both. */
__attribute__((section(".text.Effect_killByMode")))
void Effect_killByMode(int a0, int a1) {
    switch (a1) {
    case 0:
        func_00300AE8(a0, 0);
        break;
    case 1:
        Esp_killByGroupNumber(a0);
        break;
    case 2:
        Esp_killByGroupNumber(a0);
        func_00300AE8(a0, 0);
        break;
    }
}

/* sn-2.95.3-136 */



/* Make an effect vanish from one or both of its lists: mode 0 the second list, 1 the first, 2 both. */
__attribute__((section(".text.VanishEffect")))
void VanishEffect(int a0, int a1, int mode, unsigned char a3, int a4) {
    switch (mode) {
    case 0:
        func_00300AE8(a0, a4);
        break;
    case 1:
        func_002FBB78(a0, a1, a3, a4);
        break;
    case 2:
        func_002FBB78(a0, a1, a3, a4);
        func_00300AE8(a0, a4);
        break;
    }
}
