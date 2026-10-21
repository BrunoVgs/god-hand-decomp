/* sn-2.95.3-136: func_002AC1C0, cIDBase scale animation step: plays the source record's scale keys, looping or stopping at the last key. */
typedef struct {
    char unk0[8];
    short frame;
    char unkA[2];
} IdKey;

typedef struct {
    char unk0[4];
    unsigned int flags;
    char unk8[0x56];
    signed char hold;
    char unk5F[0x151];
    short keyNum;
    char unk1B2[2];
    IdKey key[8];
} IdSrcView;

typedef struct {
    void *part[5];
    char unk14[8];
    IdSrcView *src;
    char unk20[0xC];
    unsigned int flags;
    char unk30[0x10];
    float sclX;
    float sclY;
    char unk48[0x5C];
    unsigned short frame;
} IdEntView;

extern float Curve_sample(void *obj, int frame, int keyNum, void *part);

__attribute__((section(".text.func_002AC1C0")))
void func_002AC1C0(void *self, IdEntView *ent)
{
    IdSrcView *src = ent->src;
    int n;
    short last;
    float s;
    long t;

    if (!(src->flags & 0x800000))
        return;
    if (ent->flags & 0x1000)
        return;
    if (src->hold != 0)
        return;
    n = src->keyNum;
    last = src->key[n - 1].frame;
    if (!(src->flags & 0x40000)) {
        if (last < ent->frame) {
            ent->flags |= 0x1000;
            return;
        }
    } else if (last < ent->frame) {
        ent->frame = 0;
    }
    s = Curve_sample(self, (short)ent->frame, n, ent->part[2]);
    ent->sclX = s;
    ent->sclY = s;
    t = ent->flags;
    if (((unsigned long)t >> 5 & 1UL) == 0)
        ent->frame++;
}
