typedef struct {
    void *unk0;
    char pad4[4];
    signed char unk8;
} Val37A818;

typedef struct {
    char pad0[7];
    signed char unk7;
} Obj37A818;

extern int func_0037A8F8(Obj37A818 *, Val37A818 *, int);
extern void func_0037A9C8(Obj37A818 *, Val37A818 *);
extern void func_0037AAB0(Obj37A818 *, Val37A818 *);
extern void func_0037AB00(Obj37A818 *, Val37A818 *);

__attribute__((section(".text.func_0037A818")))
void func_0037A818(Obj37A818 *o, Val37A818 *v)
{
    if (v->unk8 == 0) {
        *(signed char *)v->unk0 = func_0037A8F8(o, v, *(signed char *)v->unk0);
    }
    if (v->unk8 == 1) {
        *(short *)v->unk0 = func_0037A8F8(o, v, *(short *)v->unk0);
    }
    switch (o->unk7) {
    case 0:
        func_0037A9C8(o, v);
        break;
    case 1:
        func_0037AAB0(o, v);
        break;
    case 2:
        func_0037AB00(o, v);
        break;
    }
}
