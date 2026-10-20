typedef struct { int v[5]; } Order1E6ED8;

typedef struct {
    char pad0[0x3A0];
    void *layers[14];
    unsigned char sel;
    char pad3D9[0x3E8 - 0x3D9];
    unsigned short flags;
} Scr1E6ED8;

extern Order1E6ED8 D_0042BAF0;
extern void displayScrollLayer(void *layer, int on);

__attribute__((section(".text.func_001E6ED8")))
void func_001E6ED8(Scr1E6ED8 *s, int a1, int a2)
{
    Order1E6ED8 order = D_0042BAF0;
    int i;
    int j;

    s->flags = s->sel << 11;
    if (a2) s->flags |= 0x8000;
    if (a1) {
        s->flags |= 0x4000;
        for (j = 0; j < 5; j++)
            displayScrollLayer(s->layers[order.v[j]], j == s->sel);
        return;
    }
    for (i = 0; i < 5; i++)
        displayScrollLayer(s->layers[order.v[i]], 0);
}
