/* sn-2.95.3-136, as=sn: NM closer handoff. */
typedef struct {
    char pad000[0x150];
    float sway;
    unsigned int lo : 11;
    unsigned int on : 1;
    unsigned int hi : 20;
} SwayPart;

typedef struct {
    char pad000[0x278];
    SwayPart **parts;
    char pad27C[0x2B4 - 0x27C];
    unsigned char nparts;
    char pad2B5[0x564 - 0x2B5];
    int motion;
    char pad568[0x16FC - 0x568];
    float sway;
} SwayOwner;

static inline void SwayPart_set(SwayOwner *self, SwayPart *part)
{
    if (self->sway != 0.0f) {
        part->on = 1;
        part->sway = self->sway;
    } else {
        part->sway = 0.0f;
        part->on = 0;
    }
}

static inline SwayPart *SwayOwner_part(SwayOwner *self, int i)
{
    char hold[16];
    int n = self->nparts;

    *(int *)hold = n;
    return i < n ? self->parts[i] : 0;
}

__attribute__((section(".text.func_0026A3D8")))
void func_0026A3D8(SwayOwner *self)
{
    SwayPart *part;

    float a;

    part = SwayOwner_part(self, 1);
    if (part != 0)
        SwayPart_set(self, part);
    part = SwayOwner_part(self, 2);
    if (part != 0)
        SwayPart_set(self, part);

    switch (self->motion) {
    default:
        self->sway *= 0.6f;
        break;
    case 0x223:
    case 0x275:
    case 0x276:
        self->sway *= -0.6f;
        break;
    }
    a = self->sway;
    if (a < 0.0f)
        a = -a;
    if (a <= 0.017453292f)
        self->sway = 0.0f;
}
