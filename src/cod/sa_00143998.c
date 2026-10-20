/* sn-2.95.3-136: draw the object's ID base, then redraw the second one once per active slot (0x143998). */
typedef struct IDWork143998 {
    char unk00[0x1C];
    float *src;                 /* 0x1C */
    char unk20[0x1C];
    float z;                    /* 0x3C */
    char unk40[0xF];
    unsigned char layer;        /* 0x4F */
    char unk50[0x34];
    int color;                  /* 0x84 */
} IDWork143998;

typedef struct IDObj143998 {
    char unk000[0xB0];
    char base2[0x50];           /* 0xB0 */
    float z[16];                /* 0x100 */
    int color[16];              /* 0x140 */
    char unk180[0x20];
    unsigned char layer[16];    /* 0x1A0 */
    unsigned char on[16];       /* 0x1B0 */
} IDObj143998;

extern void cIDBase_trans(void *self);
extern void cIDBase_move(void *self);
extern IDWork143998 *cIDBase_getIDWork(void *self, int idx);

__attribute__((section(".text.func_00143998")))
void func_00143998(IDObj143998 *obj)
{
    unsigned short i;
    IDWork143998 *w;

    cIDBase_trans(obj);
    i = 0;
    w = cIDBase_getIDWork(obj->base2, 0);
    for (; i < 16; i++) {
        if (obj->on[i] == 1) {
            w->z = w->src[3] + obj->z[i];
            w->layer = obj->layer[i];
            w->color = obj->color[i];
            cIDBase_move(obj->base2);
            cIDBase_trans(obj->base2);
        }
    }
}
