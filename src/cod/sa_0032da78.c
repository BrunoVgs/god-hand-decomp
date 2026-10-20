typedef struct {
    char pad0;
    unsigned char unk1;
    char pad2[2];
    int unk4;
    char pad8[0x8C - 0x8];
    int unk8C;
    int unk90;
    char pad94[0x1B2 - 0x94];
    unsigned char unk1B2;
    char pad1B3[0x1D0 - 0x1B3];
    int unk1D0;
    int unk1D4;
    int unk1D8;
    int unk1DC;
    int unk1E0;
} Obj32DA78;

extern char D_00452AA8[];
extern char D_00755C40[];
extern void Obj33F8_Tramp_0033F130_FCB0(char *msg);
extern void func_0032DBA0(Obj32DA78 *);
extern void Obj33F8_Tramp_0033B658_FC70(void);
extern void Obj33F8_Tramp_0033B670_FC88(void);
extern int func_003245B0(int, int, char *, int *, int *, int *);
extern int func_003247D0(int);
extern void func_0032F4B0(int, int);

__attribute__((section(".text.func_0032DA78")))
void func_0032DA78(Obj32DA78 *o, int a1, int a2)
{
    int v[3];

    if (o == 0) {
        Obj33F8_Tramp_0033F130_FCB0(D_00452AA8);
        return;
    }
    func_0032DBA0(o);
    Obj33F8_Tramp_0033B658_FC70();
    if (func_003245B0(a1, a2, D_00755C40, &v[0], &v[1], &v[2]) == 0) {
        o->unk1D0 = func_003247D0(a1);
        o->unk90 = o->unk8C;
        o->unk1D4 = v[0];
        o->unk1D8 = v[1];
        o->unk1DC = v[2];
        func_0032F4B0(o->unk4, o->unk90);
        o->unk1E0 = 1;
        o->unk1B2 = 1;
        o->unk1 = 1;
    }
    Obj33F8_Tramp_0033B670_FC88();
}
