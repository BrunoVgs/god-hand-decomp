#include "godhand/cCoreSave.h"
#include "godhand/player.h"

typedef struct Sys1F9C98 {
    char pad0[0x5B4];
    unsigned short stageA;
    unsigned short stageB;
} Sys1F9C98;

extern Sys1F9C98 D_007474A0;
extern char D_0061A990[];
extern void cWorldTime_setGlobalTime(void *wt, unsigned int t);
extern void func_002D9D48(void *wt, int t);

__attribute__((section(".text.cCoreSave_loadStageState")))
void cCoreSave_loadStageState(cCoreSave *self, int flag)
{
    cGameObj *pl;
    int hp;

    if (flag == 0)
        return;
    D_007474A0.stageA = self->data->saveStageA;
    D_007474A0.stageB = self->data->saveStageB;
    cCoreSave_loadSpawn(self);
    cWorldTime_setGlobalTime(D_0061A990, self->data->worldTime);
    func_002D9D48(D_0061A990, self->data->worldTimeB);
    pl = Getplayer();
    pl->hpMax = cCoreSave_getVitalMax(self);
    if (cCoreSave_getVital(self) > 0) {
        cGameObj *p2 = Getplayer();
        hp = cCoreSave_getVital(self);
        if (hp >= p2->hpMax)
            p2->hp = p2->hpMax;
        else
            p2->hp = hp;
    } else {
        cGameObj *p3 = Getplayer();
        int one = 1;
        if (one >= p3->hpMax)
            p3->hp = p3->hpMax;
        else
            p3->hp = one;
    }
    cCoreSave_loadWorldActive(self);
    cCoreSave_loadWorldToggle(self);
    cCoreSave_loadGlobalToggle(self);
}
