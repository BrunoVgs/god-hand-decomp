/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
#include "godhand/mwsfd.h"
extern int func_0034C7D0(SfdHn *hn, int index);

__attribute__((section(".text.func_003517D0")))
void func_003517D0(SfdHn *hn)
{
    SfdSeek *seek = &hn->seek;
    SfdTimPrm *cur = &hn->cur;
    int index = seek->index;

    if (seek->hdrOfs < 0)
        seek->hdrOfs = func_0034C7D0(hn, index) + 4;
    if (cur->valid < 0)
        *cur = hn->init;
}
