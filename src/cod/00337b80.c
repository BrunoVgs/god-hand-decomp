/* cygnus-2.96: stream/SFD/sound singletons. */
#include "godhand/criStm.h"

typedef struct StmVolHn {
    char unk00;
    char stat;                  /* 0x01 */
    char unk02[0x38 - 0x02];
    int vol;                    /* 0x38 */
    char unk3C[0x56 - 0x3C];
    char mode;                  /* 0x56 */
} StmVolHn;

extern int D_003E0708;
extern int D_003E0710;

__attribute__((section(".text.func_00337B80")))
void func_00337B80(StmVolHn *h, unsigned int mode)
{
    if (D_003E0710 == 1 && D_003E0708 <= 0) {
        return;
    }
    if (mode < 2 && h->mode != mode) {
        h->stat = h->mode;
        h->mode = mode;
    }
}
