/* sn-2.95.3-136: func_00377ED0, clears and numbers the three SFX object pools. */
typedef struct {
    short unk0;
    short id;
    char unk4[8];
    char flagC;
    char flagD;
    short linkE;
    short unk10;
    short link12;
    char unk14[0x3C];
} SfxPoolA;

typedef struct {
    short unk0;
    short id;
    char flag4;
    char flag5;
    char unk6[0x18];
    char flag1E;
    char unk1F;
} SfxPoolB;

typedef struct {
    short unk0;
    short id;
    char flag4;
    char flag5;
    char unk6[0x4A];
} SfxPoolC;

extern SfxPoolA D_0076B9C0[48];
extern SfxPoolB D_0076C8C0[51];
extern SfxPoolC D_0076CF20[51];
extern void *func_003A52F0(void *p, int c, int n);

__attribute__((section(".text.func_00377ED0")))
void func_00377ED0(void)
{
    int i;

    func_003A52F0(D_0076B9C0, 0, sizeof(D_0076B9C0));
    func_003A52F0(D_0076C8C0, 0, sizeof(D_0076C8C0));
    func_003A52F0(D_0076CF20, 0, sizeof(D_0076CF20));
    for (i = 0; i < 48; i++) {
        D_0076B9C0[i].id = i;
        D_0076B9C0[i].flagC = 0;
        D_0076B9C0[i].flagD = 0;
        D_0076B9C0[i].linkE = -1;
        D_0076B9C0[i].link12 = -1;
    }
    for (i = 0; i < 51; i++) {
        D_0076C8C0[i].id = i;
        D_0076CF20[i].id = i;
        D_0076C8C0[i].flag4 = 0;
        D_0076C8C0[i].flag5 = 0;
        D_0076C8C0[i].flag1E = 0;
        D_0076CF20[i].flag4 = 0;
        D_0076CF20[i].flag5 = 0;
    }
}
