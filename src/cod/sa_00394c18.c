typedef struct {
    int a;
    int b;
    int sum;
} Ent394C18;

typedef struct {
    unsigned int count;
    int check;
    Ent394C18 ent[0x400];
} Tbl394C18;

extern Tbl394C18 D_003F5520;

__attribute__((section(".text.func_00394C18")))
int func_00394C18(int a, int b)
{
    unsigned int i;

    for (i = 0; i < D_003F5520.count; i++) {
        if (D_003F5520.ent[i].b == 0) {
            D_003F5520.ent[i].a = a;
            D_003F5520.ent[i].b = b;
            D_003F5520.ent[i].sum = a ^ b ^ 0x31415926;
            return i;
        }
    }
    if (D_003F5520.count == 0x400) {
        return -1;
    }
    i = D_003F5520.count++;
    D_003F5520.ent[i].a = a;
    D_003F5520.ent[i].b = b;
    D_003F5520.ent[i].sum = a ^ b ^ 0x31415926;
    D_003F5520.check = D_003F5520.count ^ 0x31415926;
    return i;
}
