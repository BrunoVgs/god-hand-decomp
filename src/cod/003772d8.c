/* sn-2.95.3-136: func_003772D8, applies a channel command (copy params, update, key-off) to its 0xA0 channel. */
#include "godhand/seqNode.h"
typedef struct {
    char pad0[0xA];
    short cmd;   /* 0x0A */
    short ch;    /* 0x0C */
} ChanCmd;

extern void CopyChannelParams_377378(SndCh *ch, ChanCmd *c);
extern void func_00377428(SndCh *ch, ChanCmd *c);

__attribute__((section(".text.func_003772D8")))
int func_003772D8(ChanCmd *c)
{
    SndCh *ch = &D_0076E910[c->ch];

    if (ch->flags == 0)
        return -1;
    switch (c->cmd) {
    case 0:
        CopyChannelParams_377378(ch, c);
        break;
    case 1:
        func_00377428(ch, c);
        break;
    case 2:
        ch->unk16 = 1;
        break;
    }
    return 0;
}
