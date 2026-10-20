/* cygnus-2.96, -freorder-blocks dropped, as=sn: func_00351C18, maps a decoder status to an error report: 0 is fine, -2/-3 are only
 * errors when nothing was decoded, anything else reports code. */
#include "godhand/sftim.h"

extern int func_0034DD70(SftimHn *hn, int code);

__attribute__((section(".text.func_00351C18")))
int func_00351C18(SftimHn *hn, int st, int n, int code)
{
    switch (st) {
    case 0:
        return 0;
    case -2:
        if (n > 0)
            return 0;
        return func_0034DD70(hn, st);
    case -3:
        if (n > 0)
            return 0;
        return func_0034DD70(hn, st);
    default:
        return func_0034DD70(hn, code);
    }
}
