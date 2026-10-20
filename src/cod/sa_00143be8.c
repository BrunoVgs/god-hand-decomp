typedef struct IDBase143BE8 {
    char pad00[0x1C];
    unsigned char playing;
    char pad1D[0x33];
} IDBase143BE8;

typedef struct IDObj143BE8 {
    IDBase143BE8 base;
    char pad050[0x40];
    int unk90;
    char pad094[4];
    void *player;
    char pad09C[0x404];
    void *work[4];
    IDBase143BE8 base3;
    IDBase143BE8 base1;
    IDBase143BE8 base2;
    void *work3;
    void *work1;
    void *work2;
    char pad5AC[0x24];
    float speed;
    char pad5D4[4];
    unsigned int color;
    unsigned char unk5DC;
    unsigned char unk5DD;
} IDObj143BE8;

extern void *Getplayer(void);
extern void cIDBase_restartAnim(void *self);
extern void cIDBase_move(void *self);
extern void *cIDBase_getIDWork(void *self, int idx);

__attribute__((section(".text.func_00143BE8")))
void func_00143BE8(IDObj143BE8 *obj)
{
    IDBase143BE8 *b1 = &obj->base1;
    IDBase143BE8 *b2 = &obj->base2;
    IDBase143BE8 *b3 = &obj->base3;
    unsigned short i = 0;

    obj->unk90 = 0;
    obj->player = Getplayer();
    obj->speed = 20.0f;
    cIDBase_restartAnim(obj);
    obj->base.playing = 1;
    cIDBase_restartAnim(b1);
    b1->playing = 1;
    cIDBase_move(b1);
    cIDBase_restartAnim(b2);
    b2->playing = 1;
    cIDBase_move(b2);
    cIDBase_restartAnim(b3);
    b3->playing = 1;
    for (; i < 2; i++)
        obj->work[i] = cIDBase_getIDWork(obj, i);
    obj->work1 = cIDBase_getIDWork(&obj->base1, 0);
    obj->work2 = cIDBase_getIDWork(&obj->base2, 0);
    obj->work3 = cIDBase_getIDWork(&obj->base3, 0);
    obj->unk5DD = 0;
    obj->color = 0x80808080;
    obj->unk5DC = 0;
}
