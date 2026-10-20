typedef struct {
    char pad0[0x28];
    int unk28;
    char pad2C[0x60 - 0x2C];
    int stop;
    char pad64[0x990 - 0x64];
    long total0;
    long total1;
} Obj34E2C8;

extern int func_0034E3A0(Obj34E2C8 *o, int *a, int *b, int c, int *d);
extern int func_0034E4B0(Obj34E2C8 *o, int a, int b, int *n0, int *n1, int d);
extern int func_0034E460(Obj34E2C8 *o, int n);
extern void func_0034FCE0(Obj34E2C8 *o);

__attribute__((section(".text.func_0034E2C8")))
int func_0034E2C8(Obj34E2C8 *o)
{
    int a, b, d, n0, n1;
    int err = 0;
    int c = o->unk28;

    while (o->stop == 0) {
        err = func_0034E3A0(o, &a, &b, c, &d);
        if (err != 0) {
            break;
        }
        err = func_0034E4B0(o, a, b, &n0, &n1, d);
        if (err != 0) {
            break;
        }
        o->total0 += n0;
        o->total1 += n1;
        if (n0 == 0) {
            break;
        }
        err = func_0034E460(o, n0);
        if (err != 0) {
            break;
        }
    }
    func_0034FCE0(o);
    return err;
}
