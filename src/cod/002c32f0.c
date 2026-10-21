#include "godhand/gameWork.h"
typedef struct {
    char pad0[0x50];
    signed char flags;
    char pad51[0x58 - 0x51];
} RoomObjEnt;

typedef struct {
    unsigned short id;
    char pad2[0x14 - 2];
} RoomRec;

typedef struct {
    char pad0[0x1C];
    RoomObjEnt *ents;
    char pad20[0xD4 - 0x20];
    RoomRec *room;
} RoomObjList;

extern unsigned int D_00747A84;
extern RoomRec D_003C26C0[];
extern char D_005E8658[];
extern void cTaskPool_killAll(void *);
extern void func_002BEBC8(void *, int);

__attribute__((section(".text.func_002C32F0")))
void func_002C32F0(RoomObjList *o)
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
