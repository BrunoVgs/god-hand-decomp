typedef struct {
    void *unk0;
    char pad4[4];
    signed char unk8;
} MenuValue;

typedef struct {
    char pad0[7];
    signed char unk7;
} MenuValueObj;

extern int func_0037A8F8(MenuValueObj *, MenuValue *, int);
extern void func_0037A9C8(MenuValueObj *, MenuValue *);
extern void func_0037AAB0(MenuValueObj *, MenuValue *);
extern void func_0037AB00(MenuValueObj *, MenuValue *);

__attribute__((section(".text.func_0037A818")))
void func_0037A818(MenuValueObj *o, MenuValue *v)
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
