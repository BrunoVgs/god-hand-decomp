/* sn-2.95.3-136: func_0037D310, first free entry in the 24-entry bank holding n
 * (the third bank has only 3 entries). */
typedef struct {
    unsigned short active;
    char pad02[0x50 - 0x02];
} BankEnt;

extern BankEnt D_0076CF20[];

__attribute__((section(".text.func_0037D310")))
BankEnt *func_0037D310(signed char n)
{
    BankEnt *e;
    int base, cnt, i;

    base = n / 24 * 24;
    cnt = base == 48 ? 3 : 24;
    for (i = 0; i < cnt; i++) {
        e = &D_0076CF20[base + i];
        if (e->active == 0)
            return e;
    }
    return 0;
}
