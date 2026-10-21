/* sn-2.95.3-136: motion parameter lookup (0x1594A0..). */

#include "godhand/motion.h"

__attribute__((section(".text.MotionIsHaveParam")))
int MotionIsHaveParam(MotionData *mot, int kind, int sub)
{
    MotionParam *prm;
    unsigned int i;

    if (mot == 0) {
        return 0;
    }
    prm = mot->param;
    for (i = 0; i < mot->nParam; i++, prm++) {
        if (prm->kind == kind && (sub == -1 || prm->sub == sub)) {
            return 1;
        }
    }
    return 0;
}

__attribute__((section(".text.MotionGetParam")))
float MotionGetParam(MotionData *mot, int kind, int sub)
{
    MotionParam *prm;
    unsigned int i;

    if (mot != 0) {
        prm = mot->param;
        i = 0;
        if (mot->nParam != 0) {
            do {
                if (prm->kind == kind && (sub == -1 || prm->sub == sub)) {
                    return D_003BD910[prm->func](mot, prm);
                }
                i++;
                prm++;
            } while (i < mot->nParam);
        }
    }
    switch (sub) {
    default:
        return 0.0f;
    case 6:
    case 7:
    case 8:
        return 1.0f;
    }
}
