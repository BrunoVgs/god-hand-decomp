typedef struct {
    int v[7];
} Info34B198;

typedef struct Iface34B198 Iface34B198;
typedef struct {
    void *f0;
    void *f4;
    void *f8;
    void (*fC)(Iface34B198 *);
} IfaceVtbl34B198;
struct Iface34B198 {
    IfaceVtbl34B198 *vt;
};

typedef struct {
    int handle;
    Iface34B198 *iface;
    Info34B198 info;
} Req34B198;

typedef struct {
    char pad[0x2004];
    Req34B198 *req;
} Obj34B198;

extern Info34B198 D_00760D90;
extern int ReturnK_003EE2BC_00358A38_358A38(void);
extern int func_0034B270(int);
extern void func_0034B2C8(Obj34B198 *);
extern int Obj0000_Set_D_003EE2C0_34B290(int);
extern void func_00360AA8(void);

__attribute__((section(".text.func_0034B198")))
int func_0034B198(Obj34B198 *o)
{
    Req34B198 *r = o->req;
    int h = r->handle;
    Iface34B198 *iface = r->iface;

    if (h == 0) {
        return 0;
    }
    D_00760D90 = r->info;
    if (ReturnK_003EE2BC_00358A38_358A38() != 1) {
        h = func_0034B270(h);
    } else {
        func_0034B2C8(o);
        h = Obj0000_Set_D_003EE2C0_34B290(h);
    }
    iface->vt->fC(iface);
    func_00360AA8();
    return h;
}
