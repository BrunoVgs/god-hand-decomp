typedef struct Ent33C7F8 {
    short used;
    char pad2[6];
    void *pd;
    char padC[0x38 - 0xC];
    int a0;
    int a1;
    int a2;
    int a3;
    char pad48[0x78 - 0x48];
    void *cb;
    struct Ent33C7F8 *cbarg;
    void (*fn)(void);
    struct Ent33C7F8 *fnarg;
    char pad88[0x104 - 0x88];
} Ent33C7F8;

extern Ent33C7F8 D_003E9D60[];
extern void func_0033C768(void);
extern void func_0033C7A0(void);
extern void *func_003A52F0(void *dst, int val, int len);
extern void *func_0033F8B8(void);
extern void func_0033C918(Ent33C7F8 *e);
extern void func_0033C7C0(Ent33C7F8 *e);

__attribute__((section(".text.func_0033C7F8")))
Ent33C7F8 *func_0033C7F8(int a0, int a1, int a2, int a3)
{
    Ent33C7F8 *p = D_003E9D60;
    Ent33C7F8 *e;
    int i = 0;

    if (p->used != 0) {
        do {
            i++;
            p++;
            if (i >= 0x10)
                break;
        } while (p->used != 0);
    }
    if (i == 0x10)
        return 0;
    e = &D_003E9D60[i];
    func_003A52F0(e, 0, 0x104);
    e->used = 1;
    e->pd = func_0033F8B8();
    if (e->pd == 0) {
        func_0033C918(e);
        return 0;
    }
    e->cb = (char *)func_0033C768 + 8;
    e->a0 = a0;
    e->a1 = a1;
    e->a2 = a2;
    e->a3 = a3;
    e->fn = func_0033C7A0;
    e->cbarg = e;
    e->fnarg = e;
    func_0033C7C0(e);
    return e;
}
