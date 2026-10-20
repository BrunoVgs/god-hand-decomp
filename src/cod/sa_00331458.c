typedef struct Mgr331458 {
    char unk0;
    signed char mode;
} Mgr331458;

typedef struct Req331458 {
    char unk0[2];
    signed char state;
} Req331458;

extern Mgr331458 D_003D8410;
extern int D_003D844C;
extern int D_003D846C;
extern void Forward33B568_33B658(void);
extern void Forward33B5C8_33B670(void);
extern void func_003312B8(void);
extern void func_003312E8(Req331458 *r);
extern void func_00331310(Req331458 *r);

__attribute__((section(".text.func_00331458")))
void func_00331458(Req331458 *r)
{
    short i;
    signed char state;
    Mgr331458 *m;

    for (i = 0; i < 1000; i++) {
        Forward33B568_33B658();
        if (D_003D844C == 1) {
            Forward33B5C8_33B670();
            func_003312B8();
            continue;
        }
        D_003D844C = 1;
        Forward33B5C8_33B670();
        break;
    }
    state = r->state;
    if (state == 2) {
        m = &D_003D8410;
        if (m->mode == 1)
            func_003312E8(r);
        if (m->mode == state)
            func_00331310(r);
        if (r->state != 9) {
            r->state = 3;
            D_003D846C++;
        }
    }
    D_003D844C = 0;
}
