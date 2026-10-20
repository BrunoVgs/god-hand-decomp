typedef struct Res305A68 {
    char pad00[0x14];
    int ofs14;
    char pad18[4];
    int ofs1C;
} Res305A68;

typedef struct GW305A68 {
    char pad000[0x550];
    Res305A68 *res;
    char pad554[0x5AC - 0x554];
    void *data;
} GW305A68;

typedef struct Esp305A68 {
    char pad000[0x41C];
    unsigned char active;
} Esp305A68;

extern GW305A68 D_007474A0;
extern char D_00741DC8[];
extern char D_00743250[];
extern char D_00450068[];
extern char D_00450070[];
extern char D_00450078[];
extern void EmitterAllKill(void);
extern void EspAllKill(void);
extern void func_003057A0(Esp305A68 *self);
extern void func_00305BC0(Esp305A68 *self);
extern void func_00306A88(void *p);
extern void espSys_effDataRegist(Esp305A68 *self, int id, void *data);
extern void *SearchData(void *name, void *table, int which);
extern void func_00305C10(Esp305A68 *self, void *data);
extern void func_00305C18(Esp305A68 *self, void *data);
extern void func_00306D18(void *p);

__attribute__((section(".text.func_00305A68")))
void func_00305A68(Esp305A68 *self)
{
    void *p;

    self->active = 0;
    EmitterAllKill();
    EspAllKill();
    func_003057A0(self);
    func_00305BC0(self);
    func_00306A88(D_00741DC8);
    espSys_effDataRegist(self, 0, (void *)(D_007474A0.res->ofs14 + (int)D_007474A0.res));
    espSys_effDataRegist(self, 0x58, (void *)(D_007474A0.res->ofs1C + (int)D_007474A0.res));
    espSys_effDataRegist(self, 4, (void *)(D_007474A0.res->ofs14 + (int)D_007474A0.res));
    p = SearchData(D_007474A0.data, D_00450068, 0);
    if (p != 0) {
        espSys_effDataRegist(self, 1, p);
    }
    p = SearchData(D_007474A0.data, D_00450070, 0);
    if (p != 0) {
        func_00305C10(self, p);
    }
    p = SearchData(D_007474A0.data, D_00450078, 0);
    if (p != 0) {
        func_00305C18(self, p);
    }
    func_00306D18(D_00743250);
}
