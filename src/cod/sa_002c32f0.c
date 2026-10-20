typedef struct {
    char pad0[0x50];
    signed char flags;
    char pad51[0x58 - 0x51];
} Ent2C32F0;

typedef struct {
    unsigned short id;
    char pad2[0x14 - 2];
} Room2C32F0;

typedef struct {
    char pad0[0x1C];
    Ent2C32F0 *ents;
    char pad20[0xD4 - 0x20];
    Room2C32F0 *room;
} Obj2C32F0;

typedef struct {
    char pad0[0x5B0];
    unsigned short room;
} Game2C32F0;

extern unsigned int D_00747A84;
extern Room2C32F0 D_003C26C0[];
extern Game2C32F0 D_007474A0;
extern char D_005E8658[];
extern void cTaskPool_killAll(void *);
extern void func_002BEBC8(void *, int);

__attribute__((section(".text.func_002C32F0")))
void func_002C32F0(Obj2C32F0 *o)
{
    unsigned int i;

    cTaskPool_killAll(&o->ents);
    D_00747A84 &= ~0x40000000;
    for (i = 0; i < 16; i++) {
        if ((int)i >= 0) {
            o->ents[i].flags &= ~1;
        }
    }
    o->room = D_003C26C0;
    while (o->room->id != 0xFFFF && o->room->id != D_007474A0.room) {
        o->room++;
    }
    func_002BEBC8(D_005E8658, D_007474A0.room);
}
