/* cygnus-2.96 matched TU. */
#include "godhand/criStm.h"

extern void *func_003A52F0(void *dst, int val, int len);

/* Resets the pending-async slot of an AsyncCall: clears the 16-byte work area
   and seeds the two fader shorts to -0x80. */
__attribute__((section(".text.func_0033C7C0")))
void func_0033C7C0(AsyncCall *e)
{
    *(int *)((char *)e + 0xCC) = 0;
    *(short *)((char *)e + 0xE0) = 0;
    *(short *)((char *)e + 0xE2) = -0x80;
    *(short *)((char *)e + 0xE4) = -0x80;
    func_003A52F0((char *)e + 0xD0, 0, 0x10);
}
