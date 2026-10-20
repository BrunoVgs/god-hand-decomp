typedef struct {
    int unk0;
    int unk4;
} Res333C00;

typedef struct {
    int unk0;
    int unk4;
} Tbl333C00;

extern char D_004545B0[];
extern char D_004545B8[];
extern Tbl333C00 D_003D9DC0;
extern int func_003A5678(char *, char *);
extern void func_003260C8(char *, int);
extern int func_00333B00(char *);
extern void func_00333B40(char *, int *, int *);
extern void func_00333A10(Res333C00 *, char *, void *, int);

__attribute__((section(".text.func_00333C00")))
int func_00333C00(char *name, Res333C00 *res)
{
    int buf[2];

    if (func_003A5678(D_004545B0, name) == 0) {
        res->unk4 = -1;
        res->unk0 = 0;
        func_003260C8(D_004545B8, 0x2E);
        return 1;
    }
    if (func_00333B00(name) == 1) {
        func_00333B40(name, &buf[0], &buf[1]);
        res->unk0 = buf[0];
        res->unk4 = buf[1] << 11;
        return 0;
    }
    res->unk0 = 0;
    res->unk4 = 0;
    if (D_003D9DC0.unk0 != 0) {
        func_00333A10(res, name, (void *)D_003D9DC0.unk0, D_003D9DC0.unk4);
    }
    return 0;
}
