/* cygnus-2.96: Sofdec picture-buffer put/advance wrappers (0x3568B8..). */

#include "godhand/sftim.h"

extern int func_00356358(SftimHn *hn);
extern int sfmpvp_PutVibuf(ViBuf *b, unsigned int src, int len);
extern int func_00355C08(ViBuf *b, int n);

__attribute__((section(".text.func_003568B8")))
int func_003568B8(SftimHn *hn, unsigned int src, int len)
{
    if (func_00356358(hn) == 0) {
        return len;
    }
    return sfmpvp_PutVibuf(SFD_WORK_VIBUF(hn->work), src, len);
}

__attribute__((section(".text.func_00356928")))
int func_00356928(SftimHn *hn, int n)
{
    if (func_00356358(hn) == 0) {
        return n;
    }
    return func_00355C08(SFD_WORK_VIBUF(hn->work), n);
}
