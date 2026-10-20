typedef struct {
    char pad0[4];
    int unk4;
    char pad8[4];
    int unkC;
    int unk10;
    char *unk14;
    char pad18[4];
    void (*unk1C)(int, int);
    int unk20;
} Strm338FD8;

typedef struct {
    char *unk0;
    int unk4;
} Res338FD8;

extern char D_004559D0[];
extern char D_00455920[];
extern char D_004559E0[];
extern char D_00455950[];
extern void func_00338A48(char *, char *);

__attribute__((section(".text.func_00338FD8")))
void func_00338FD8(Strm338FD8 *s, int mode, int size, Res338FD8 *res)
{
    int n;
    int pos;

    if (s == 0) {
        func_00338A48(D_004559D0, D_00455920);
        return;
    }
    if (s->unk4 == 0) {
        func_00338A48(D_004559E0, D_00455950);
        return;
    }
    if (mode == 0) {
        res->unk4 = 0;
        res->unk0 = 0;
        return;
    }
    if (mode == 1) {
        n = s->unkC;
        if (n >= size) {
            n = size;
        }
        res->unk4 = n;
        pos = s->unk10;
        s->unk10 = pos + n;
        res->unk0 = s->unk14 + pos;
        s->unkC -= res->unk4;
        return;
    }
    res->unk4 = 0;
    res->unk0 = 0;
    if (s->unk1C != 0) {
        s->unk1C(s->unk20, -3);
    }
}
