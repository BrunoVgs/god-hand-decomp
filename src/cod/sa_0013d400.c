typedef struct IDWork13D400 {
    char pad0[0x40];
    int unk40;
    char pad44[0x34];
    int unk78;
} IDWork13D400;

typedef struct CustomIDWork13D400 {
    char pad[0x7C];
} CustomIDWork13D400;

typedef struct Obj13D400 {
    char pad0[0x90];
    unsigned char on;
    char pad91;
    short unk92;
    IDWork13D400 *work[11];
    char padC0[0x10];
    char base2[0x50];
    CustomIDWork13D400 cw[5];
    char pad38C;
} Obj13D400;

extern void cIDBase_initIDWork(void *self, int idx);
extern IDWork13D400 *cIDBase_getIDWork(void *self, int idx);
extern void cIDBase_restartAnim(void *self);
extern void cIDBase_move(void *self);
extern void func_002AC9B8(void *self, IDWork13D400 *w, int a2);
extern void CustomIDWork_Initialize(CustomIDWork13D400 *cw, IDWork13D400 *w);
extern void CustomIDWork_SetDisp(CustomIDWork13D400 *cw, int on);
extern void CustomIDWork_Main(CustomIDWork13D400 *cw);

__attribute__((section(".text.func_0013D400")))
void func_0013D400(Obj13D400 *obj)
{
    unsigned short i;
    int j, k;

    obj->unk92 = 0;
    for (i = 0; i < 11; i++) {
        cIDBase_initIDWork(obj, i);
        obj->work[i] = cIDBase_getIDWork(obj, i);
        func_002AC9B8(obj, obj->work[i], 0);
    }
    cIDBase_restartAnim(obj);
    obj->on = 1;
    obj->work[4]->unk78 = 0;
    obj->work[4]->unk40 = 0;
    cIDBase_move(obj);
    cIDBase_restartAnim(obj->base2);
    for (j = 0; j < 5; j++) {
        CustomIDWork_Initialize(&obj->cw[j], cIDBase_getIDWork(obj->base2, j));
        CustomIDWork_SetDisp(&obj->cw[j], 0);
    }
    for (k = 0; k < 5; k++)
        CustomIDWork_Main(&obj->cw[k]);
    cIDBase_move(obj->base2);
    obj->pad38C = 0;
}
