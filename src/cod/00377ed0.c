/* sn-2.95.3-136: func_00377ED0, clears and numbers the three SFX object pools. */
#include "godhand/seqNode.h"
typedef struct {
    short unk0;
    short id;
    char unk4[8];
    char flagC;
    char flagD;
    short linkE;
    short unk10;
    short link12;
    char unk14[0x3C];
} SfxPoolA;

extern SfxPoolA D_0076B9C0[48];
extern void *func_003A52F0(void *p, int c, int n);

__attribute__((section(".text.func_00377ED0")))
void func_00377ED0(void)
{
    int i;

    func_003A52F0(D_0076B9C0, 0, sizeof(D_0076B9C0));
    func_003A52F0(D_0076C8C0, 0, sizeof(D_0076C8C0));
    func_003A52F0(D_0076CF20, 0, sizeof(D_0076CF20));
    for (i = 0; i < 48; i++) {
        D_0076B9C0[i].id = i;
        D_0076B9C0[i].flagC = 0;
        D_0076B9C0[i].flagD = 0;
        D_0076B9C0[i].linkE = -1;
        D_0076B9C0[i].link12 = -1;
    }
    for (i = 0; i < SEQ_NUM; i++) {
        D_0076C8C0[i].id = i;
        D_0076CF20[i].id = i;
        D_0076C8C0[i].unk04 = 0;
        D_0076C8C0[i].kind = 0;
        D_0076C8C0[i].unk1E = 0;
        D_0076CF20[i].unk04 = 0;
        D_0076CF20[i].kind = 0;
    }
}
