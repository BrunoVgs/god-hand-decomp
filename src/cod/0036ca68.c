/* cygnus-2.96: clear a 0x128-byte work block and set its channel count to 8 (0x36CA68). */

#include "godhand/criStm.h"

typedef struct ChWork {
    int unk00;
    int nch;                    /* 0x04 */
    char unk08[0x128 - 0x08];
} ChWork;

extern ChWork D_003F1EC8;

__attribute__((section(".text.func_0036CA68")))
void func_0036CA68(void)
{
    ChWork *w = &D_003F1EC8;

    func_003A52F0(w, 0, sizeof(ChWork));
    w->nch = 8;
}
