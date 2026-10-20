/* cygnus-2.96: func_0036C6C8, programs four 3-word channel params plus globals into the device, then commits. */
typedef struct {
    int a;
    int b;
    int c;
} ChanParam;

typedef struct {
    char unk0[0x3B4];
    int dev;
    int unk3B8;
    ChanParam ch[4];
    int p0;
    int p1;
    char unk3F4[4];
} DevObj;

extern int Obj0000_Get_D_003F1FF0_36CCA8(void);
extern void func_0036CDC0(int dev, int idx, int a, int b, int c);
extern void func_0036CDE8(int dev, int p0, int p1);
extern int func_0036CE38(int dev, int arg);
extern void func_0036CE10(int dev, int zero, void *buf);
extern void func_0036C790(DevObj *obj);

__attribute__((section(".text.func_0036C6C8")))
int func_0036C6C8(DevObj *obj, int arg)
{
    ChanParam *ch;
    int i;

    if (Obj0000_Get_D_003F1FF0_36CCA8() != 0) {
        i = 0;
        ch = obj->ch;
        do {
            func_0036CDC0(obj->dev, i, ch->a, ch->b, ch->c);
            i++;
            ch++;
        } while (i < 4);
        func_0036CDE8(obj->dev, obj->p0, obj->p1);
        if (func_0036CE38(obj->dev, arg) != 0)
            return -2;
        func_0036CE10(obj->dev, 0, obj->unk3F4);
        func_0036C790(obj);
        return 0;
    }
    return -1;
}
