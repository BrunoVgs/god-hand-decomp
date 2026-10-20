typedef struct {
    char pad[0x75];
    char f75;
    char f76;
} PhaseAObj;

typedef struct {
    PhaseAObj *obj;
    int a;
    int b;
} PhaseAEnt;

typedef struct {
    char pad[0x22F4];
    PhaseAEnt e[17];
} PhaseAOwner;

extern char D_005FEE00[];

__attribute__((section(".text.func_001415E8")))
void func_001415E8(PhaseAOwner *p, int value)
{
    int i;
    for (i = 0; i < 17; i++) {
        PhaseAObj *obj = p->e[i].obj;
        if (obj != 0) {
            obj->f75 = 1;
            obj->f76 = value;
        }
    }
}
