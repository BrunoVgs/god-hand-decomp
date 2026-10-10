/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"
#include "godhand/vu0.h"

/* sn-2.95.3-136 */



#define COMBASE_F0_BIT2   0x04          /* flags0 bit 2 */

/* Start the knock step: aim the knock vector from the anchor body at the object, set mode 2 step 0, and flag the object active. */
__attribute__((section(".text.func_0018E918")))
void func_0018E918(cOmBase *self)
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
__attribute__((section(".text.func_001900C8")))
void func_001900C8(cOmBase *self)
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
__attribute__((section(".text.func_00199CC8")))
void func_00199CC8(cOmBase *self)
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
__attribute__((section(".text.func_0019FDB0")))
void func_0019FDB0(cOmBase *self)
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
__attribute__((section(".text.func_001746B0")))
void func_001746B0(cOmBase *self)
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
__attribute__((section(".text.func_001754B0")))
void func_001754B0(cOmBase *self)
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
