typedef struct Pad1B48E0 {
    char pad[0x574];
    float frameRate;
} Pad1B48E0;

typedef struct Mdl1B48E0 {
    char pad0[0x104];
    float rot;
} Mdl1B48E0;

typedef struct Em1B48E0 {
    char pad0[0x278];
    Mdl1B48E0 **mdl;
    char pad27C[0x38];
    unsigned char hasMdl;
    char pad2B5[0x41];
    unsigned char spinStep;
    char pad2F7[0x325];
    float spinMax;
    float spin;
    float spinUp;
    float spinDown;
} Em1B48E0;

extern Pad1B48E0 D_007474A0;
extern char D_005864F0[];
extern float cEmManage_GetSpeedRate(void *mgr);

__attribute__((section(".text.func_001B48E0")))
void func_001B48E0(Em1B48E0 *em)
{
    int hold[4];
    Mdl1B48E0 *m;
    float v, lim;

    switch (em->spinStep) {
    case 0:
        em->spinStep = 1;
        em->spin = 0.0f;
        break;
    case 1:
        break;
    case 2:
        v = em->spin + em->spinUp * cEmManage_GetSpeedRate(D_005864F0) * D_007474A0.frameRate;
        lim = em->spinMax;
        em->spin = v;
        if (lim <= v)
            em->spin = lim;
        break;
    case 3:
        v = em->spin - em->spinDown * cEmManage_GetSpeedRate(D_005864F0) * D_007474A0.frameRate;
        em->spin = v;
        if (v <= 0.0f)
            em->spin = 0.0f;
        break;
    }
    hold[0] = em->hasMdl;
    if (hold[0] != 0)
        m = *em->mdl;
    else
        m = 0;
    m->rot = m->rot + em->spin * cEmManage_GetSpeedRate(D_005864F0) * D_007474A0.frameRate;
}
