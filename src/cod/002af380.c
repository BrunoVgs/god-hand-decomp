/* sn-2.95.3-136: counts the printable codes of a message up to its 0x80xx end code. */
#include "godhand/cMessDrawFontCode.h"

__attribute__((section(".text.func_002AF380")))
int func_002AF380(unsigned short id)
{
    unsigned short *p;
    int n = 0;

    p = cMessage_getMessageAddr(D_003C23A4, id);
    while (1) {
        if ((*p >> 15) != 0) {
            if ((*p & 0xFF00) == 0x8000) {
                break;
            }
        } else {
            n++;
        }
        p += cMessCommon_getCodeSize(*p);
    }
    return n;
}
