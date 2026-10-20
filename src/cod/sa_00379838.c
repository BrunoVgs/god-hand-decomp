/* sn-2.95.3-136: NM closer handoff. */
typedef struct {
    short unk0;
    short unk2;
    short unk4;
    short y;
    char pad8[0xC];
} Ent379838;

typedef struct {
    char pad0[7];
    signed char mode;
    char pad8[0x25 - 0x8];
    signed char idx;
} Obj379838;

extern Ent379838 D_003F21E8[];
extern Ent379838 D_003F2368[];
extern Ent379838 D_003F24D0[];
extern char D_0045B758[];
extern char D_0045B760[];
extern void func_002E0DE8(int, int, int, char *);

__attribute__((section(".text.func_00379838")))
void func_00379838(Obj379838 *o)
{
    int y = 3;

    switch (o->mode) {
    case 0:
        y = (D_003F21E8 + o->idx)->y + 3;
        break;
    case 1:
        y = (D_003F2368 + o->idx)->y + 3;
        break;
    case 2:
        y = (D_003F24D0 + o->idx)->y + 3;
        break;
    }
    {
        short sy = y;
        func_002E0DE8(0x19, sy, 0xC, D_0045B758);
        func_002E0DE8(0x2E, sy, 0xC, D_0045B760);
    }
}
