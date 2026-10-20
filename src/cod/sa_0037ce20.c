typedef struct {
    unsigned short flags;
    unsigned char b2;
    unsigned char b3;
    int w4;
    int w8;
    unsigned short hC;
    unsigned short hE;
    unsigned short h10;
    unsigned short h12;
    unsigned short h14;
    unsigned short h16;
    unsigned short h18;
    unsigned short h1A;
    unsigned short h1C;
    char pad1E[2];
} SndVoiceOut;

typedef struct {
    unsigned short flags;
    char pad2[2];
    unsigned char b4;
    unsigned char kind;
    char pad6[0xA];
    int owner;
    int w14;
    unsigned short h18;
    unsigned short h1A;
    unsigned short h1C;
    unsigned short h1E;
    unsigned short h20;
    unsigned short h22;
    char pad24[0x26];
    unsigned short h4A;
    unsigned short h4C;
    unsigned short h4E;
} SndVoiceIn;

extern SndVoiceOut D_0076A9C0[];
extern SndVoiceIn D_0076CF20[];

__attribute__((section(".text.func_0037CE20")))
void func_0037CE20(void)
{
    int i;

    for (i = 0; i < 48; i++) {
        SndVoiceIn *s = &D_0076CF20[i];
        SndVoiceOut *d = &D_0076A9C0[i];
        if (s->flags == 0) {
            d->flags = 0;
            d->w4 = 0;
            d->w8 = 0;
        } else {
            d->flags = s->flags;
            d->b2 = s->b4;
            d->b3 = s->kind;
            d->w4 = s->owner;
            d->w8 = s->w14;
            d->hC = s->h1C;
            d->hE = s->h1E;
            d->h10 = s->h20;
            d->h12 = s->h18;
            d->h14 = s->h1A;
            d->h16 = s->h22;
            d->h18 = s->h4A;
            d->h1A = s->h4C;
            d->h1C = s->h4E;
        }
    }
}
