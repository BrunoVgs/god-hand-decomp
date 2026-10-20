/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_0030FB20, split from src/cod/batch29_nm.c by the NM closer. */
#include "godhand/vu0.h"

extern void cEmSetParam_updateSetDataFlag(void *set, int id, unsigned int flags);
extern char D_00586AB0[];
extern void *func_002D50C0(void *a0);
extern int D_0044D1A8;
typedef struct { unsigned char b[16]; } Quad16_b29;
extern Quad16_b29 D_005FEB00;
extern int func_00151630(void *a0);
extern void CustomIDWork_SetLocalPosX(void *a0, int x);
extern int D_00747A0C;
extern void func_001EC088(void *a0);
extern char D_003BE528[];
extern int func_0030FCC0(void *a0);
extern char D_00770850[];

__attribute__((section(".text.func_0030FB20")))
void *func_0030FB20(void *unused, char *obj)
{
    if (obj != 0) {
        if (func_0030FCC0(obj) != 0)
            return obj;
        {
            char *vt = *(char **)(obj + 0x214);
            (*(void (**)(void *, int))(vt + 0xC))(obj + *(short *)(vt + 8), 3);
        }
    }
    return 0;
}

