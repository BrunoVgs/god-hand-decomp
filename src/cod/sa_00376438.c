/* sn-2.95.3-136: NM closer handoff. */
typedef struct {
    int wait;
    unsigned char bank;
    unsigned char op;
    char unk6[0xA];
} SeqCmd;

typedef struct {
    char data[0x14];
} SeqWork;

typedef struct SeqObj {
    unsigned short flags;
    char unk2[0x2E];
    SeqCmd *cmd;
    char unk34[4];
    int wait;
    signed char bank;
    signed char op;
    char unk3E[2];
    SeqWork work[1];
} SeqObj;

extern int (*D_003F2188[])(SeqObj *o, SeqWork *w);

__attribute__((section(".text.func_00376438")))
void func_00376438(SeqObj *o)
{
    int r;

    for (;;) {
        int w = o->wait;
        __asm__ volatile("nop");
        if (w == 0) {
        again:
            r = D_003F2188[o->op](o, &o->work[o->bank]);
            if (o->flags & 0x1000)
                break;
            if (r == 0)
                o->cmd++;
            o->wait = o->cmd->wait;
            o->bank = o->cmd->bank;
            o->op = o->cmd->op;
            if (o->wait != 0) {
                o->wait--;
                break;
            }
            goto again;
        } else {
            o->wait--;
            break;
        }
    }
}
