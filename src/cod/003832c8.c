#include "godhand/menuCtl.h"
typedef struct {
    char pad0[0x1C];
    short x[5];
    short y[5];
    char pad30[4];
    SndVoiceRef info;
    char pad68[0xA4 - 0x68];
    SndTrkSet grp;
} MenuGrpCtl;

extern void *func_0032DCD0(void *ply, int n);
extern void func_0032A6D0(void *adxt, int a1, int a2);

__attribute__((section(".text.func_003832C8")))
void func_003832C8(void *ctl, MenuGrpCtl *m, unsigned char multi)
{
    SndTrkSet *g;
    SndVoiceRef *info;
    int i;
    void *h;

    if (multi) {
        g = &m->grp;
        for (i = 0; i < g->count; i++) {
            h = func_0032DCD0(g->ply, i);
            func_0032A6D0(h, 0, m->x[i + 1]);
            func_0032A6D0(h, 1, m->y[i + 1]);
        }
    } else {
        info = &m->info;
        func_0032A6D0(info->voice, 0, m->x[0]);
        func_0032A6D0(info->voice, 1, m->y[0]);
    }
}
