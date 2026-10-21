typedef struct {
    char pad0[0x284];
    int unk284;
    int unk288;
} SfdTimer;

extern int sfply_IsAnyoneTerm(char *);
extern int GetArrayElemA0C_35A1C8(char *, int);
extern int func_00357DA0(char *);
extern int func_00357E58(char *);
extern int func_0035AB98(char *, int *, int *);
extern int func_0036C920(int, int, int);
extern int func_0035AEC8(int, int, int, int);

__attribute__((section(".text.func_00357C20")))
int func_00357C20(char *o)
{
    int t[2];
    SfdTimer *tm;
    int rate;
    int now;

    if (sfply_IsAnyoneTerm(o) != 0) {
        return 1;
    }
    if (GetArrayElemA0C_35A1C8(o, 5) == 1 && func_00357DA0(o) != 0) {
        return 1;
    }
    if (GetArrayElemA0C_35A1C8(o, 6) == 1 && func_00357E58(o) != 0) {
        return 1;
    }
    func_0035AB98(o, &t[0], &t[1]);
    tm = (SfdTimer *)(o + 0xD30);
    rate = tm->unk288;
    now = tm->unk284;
    return func_0035AEC8(t[0], t[1], now - func_0036C920(GetArrayElemA0C_35A1C8(o, 0x45), rate, 1000000), rate) != 0;
}
