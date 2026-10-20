/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_003778D8, split from src/cod/batch51_nm.c by the NM closer. */
typedef struct {
    unsigned short flags;
    unsigned char b2;
    unsigned char b3;
    int w4;
    unsigned short h8;
    unsigned short hA;
    unsigned short hC;
    unsigned short hE;
    int w10[6];
    char pad28[0x18];
} SndChOut;

typedef struct {
    unsigned short flags;
    char pad2[2];
    int w4;
    unsigned short h8;
    unsigned short hA;
    unsigned short hC;
    unsigned char bE;
    unsigned char bF;
    char pad10[2];
    unsigned short h12;
    char pad14[0x64];
    int w78[6];
    char pad90[0x10];
} SndChIn;

extern SndChOut D_0076AFC0[];
extern SndChIn D_0076E910[];

__attribute__((section(".text.func_003778D8")))
void func_003778D8(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        SndChIn *s = &D_0076E910[i];
        SndChOut *d = &D_0076AFC0[i];
        if (s->flags == 0) {
            d->flags = 0;
            d->w4 = 0;
        } else {
            d->flags = s->flags;
            d->b2 = s->bE;
            d->b3 = s->bF;
            d->w4 = s->w4;
            d->h8 = s->h8;
            d->hA = s->hA;
            d->hC = s->hC;
            d->hE = s->h12;
            d->w10[0] = s->w78[0];
            d->w10[1] = s->w78[1];
            d->w10[2] = s->w78[2];
            d->w10[3] = s->w78[3];
            d->w10[4] = s->w78[4];
            d->w10[5] = s->w78[5];
        }
    }
}
