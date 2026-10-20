/* sn-2.95.3-136: func_003772D8, applies a channel command (copy params, update, key-off) to its 0xA0 channel. */
typedef struct {
    char pad0[0xA];
    short cmd;   /* 0x0A */
    short ch;    /* 0x0C */
} ChanCmd;

extern char D_0076E910[];
extern void CopyChannelParams_377378(char *ch, ChanCmd *c);
extern void func_00377428(char *ch, ChanCmd *c);

__attribute__((section(".text.func_003772D8")))
int func_003772D8(ChanCmd *c)
{
    char *ch = D_0076E910 + c->ch * 0xA0;

    if (*(unsigned short *)ch == 0)
        return -1;
    switch (c->cmd) {
    case 0:
        CopyChannelParams_377378(ch, c);
        break;
    case 1:
        func_00377428(ch, c);
        break;
    case 2:
        *(short *)(ch + 0x16) = 1;
        break;
    }
    return 0;
}
