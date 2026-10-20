typedef struct {
    int unk0;
    int unk4;
    char pad8[0x3C - 0x8];
    int sfd;
    int unk40;
    int pad44;
    int unk48;
    char pad4C[0x284 - 0x4C];
    char q0[0x20];
    char q1[0x20];
    char pad2C4[0x2CC - 0x2C4];
    int unk2CC;
    char pad2D0[0x2DC - 0x2D0];
    int unk2DC;
    int unk2E0;
    int unk2E4;
    int unk2E8;
    char pad2EC[0x2FC - 0x2EC];
    int unk2FC;
    int unk300;
} Mwsf345DF0;

extern char D_00458068[];
extern void mwlSfdSleepDecSvr(void);
extern int func_00358968(int);
extern void func_00345750(int);
extern void MWSFSVM_Error(char *msg);
extern void func_00348498(void *);
extern void func_00349B60(int);
extern void func_00335950(int);

__attribute__((section(".text.func_00345DF0")))
void func_00345DF0(Mwsf345DF0 *o)
{
    int sfd = o->sfd;

    if (sfd == 0) {
        return;
    }
    mwlSfdSleepDecSvr();
    o->unk4 = 0;
    o->sfd = 0;
    if (func_00358968(sfd) != 0) {
        func_00345750(-0x134);
        MWSFSVM_Error(D_00458068);
    }
    o->sfd = sfd;
    func_00348498(o->q0);
    func_00348498(o->q1);
    o->unk2CC = 0;
    if (o->unk40 != 0) {
        func_00349B60(o->unk40);
    }
    if (o->unk48 != 0) {
        func_00335950(o->unk48);
    }
    if (o->unk2E0 == 0) {
        o->unk2E4 = 0;
        o->unk2FC = -1;
        o->unk2DC = 0;
        o->unk300 = 0;
        o->unk2E8 = 0;
        return;
    }
    o->unk2E8 = 2;
}
