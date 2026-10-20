/* sn-2.95.3-136: func_002D0658, sets the volume of BGM table entry `id` (0 = default), fading all others. */
typedef struct {
    unsigned short id;
    short vol;
    char unk4[8];
} BgmEnt;

typedef struct {
    char unk0[0x30];
    int active;
    char unk34[0x24];
    int curVol;
} SndCtx;

typedef struct {
    char unk0[0x5B0];
    unsigned short bgmId;
} GameWork;

extern GameWork D_007474A0;
extern BgmEnt *func_002D05D8(SndCtx *snd, int group, int *count);
extern void cSnd_SetBgmFadeOutTimeAll(SndCtx *snd, float t);

__attribute__((section(".text.func_002D0658")))
void func_002D0658(SndCtx *snd, int vol, int id, float t)
{
    BgmEnt *e;
    int count;
    int i;

    if (snd->active == 0)
        return;
    if (vol == 0)
        vol = (int)0x80000000;
    e = func_002D05D8(snd, id >> 8, &count);
    if (e == 0)
        return;
    cSnd_SetBgmFadeOutTimeAll(snd, t);
    for (i = 0; i < count; i++, e++) {
        if (e->id == id) {
            e->vol = vol;
            if (id == D_007474A0.bgmId)
                snd->curVol = vol;
            return;
        }
    }
}
