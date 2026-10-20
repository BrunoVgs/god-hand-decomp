/* sn-2.95.3-136: func_0037A740, looks up the object's entry in one of three 0x14-byte tables by kind and runs its handler when any 0xF000 flag is set. */
typedef struct {
    char unk0[9];
    signed char handler;
    char unkA[0xA];
} ActEnt;

typedef struct {
    char unk0[7];
    signed char kind;
    char unk8[0x1D];
    signed char idx;
    char unk26[0x12];
    unsigned int flags;
} MenuActObj;

extern ActEnt D_003F21E8[];
extern ActEnt D_003F2368[];
extern ActEnt D_003F24D0[];
extern void (*D_003F2628[])(MenuActObj *obj, ActEnt *e);

__attribute__((section(".text.func_0037A740")))
int func_0037A740(MenuActObj *obj)
{
    ActEnt *e = 0;

    switch (obj->kind) {
    case 0:
        e = &D_003F21E8[obj->idx];
        break;
    case 1:
        e = &D_003F2368[obj->idx];
        break;
    case 2:
        e = &D_003F24D0[obj->idx];
        break;
    }
    if ((obj->flags & 0xF000) == 0)
        return 0;
    D_003F2628[e->handler](obj, e);
    return 1;
}
