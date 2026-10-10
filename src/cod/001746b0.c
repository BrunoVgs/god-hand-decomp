/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"
#include "godhand/vu0.h"

/* sn-2.95.3-136 */



#define COMBASE_F0_BIT2   0x04          /* flags0 bit 2 */

/* Start the knock step: aim the knock vector from the anchor body at the object, set mode 2 step 0, and flag the object active. */
__attribute__((section(".text.cOmBase_startKnockStepF")))
void cOmBase_startKnockStepF(cOmBase *self)
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
__attribute__((section(".text.cOmBase_startKnockStepG")))
void cOmBase_startKnockStepG(cOmBase *self)
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
__attribute__((section(".text.cOmBase_startKnockStepH")))
void cOmBase_startKnockStepH(cOmBase *self)
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
__attribute__((section(".text.cOmBase_startKnockStepI")))
void cOmBase_startKnockStepI(cOmBase *self)
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
__attribute__((section(".text.cOmBase_startKnockStepJ")))
void cOmBase_startKnockStepJ(cOmBase *self)
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
__attribute__((section(".text.cOmBase_startKnockStepK")))
void cOmBase_startKnockStepK(cOmBase *self)
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
