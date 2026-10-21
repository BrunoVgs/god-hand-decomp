typedef struct {
    char pad[0x75];
    char f75;
    char f76;
} MarkObj;

typedef struct {
    MarkObj *obj;
    int a;
    int b;
} MarkEnt;

typedef struct {
    char pad[0x22F4];
    MarkEnt e[17];
} MarkOwner;


__attribute__((section(".text.func_001415E8")))
void func_001415E8(MarkOwner *p, int value)
{
    int i;
    for (i = 0; i < 17; i++) {
        MarkObj *obj = p->e[i].obj;
        if (obj != 0) {
            obj->f75 = 1;
            obj->f76 = value;
        }
    }
}
