/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_00394D00, split from src/cod/batch31_nm.c by the NM closer. */
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

__attribute__((section(".text.func_00394D00")))
int func_00394D00(int key)
{
    unsigned int i;

    for (i = 0; i < D_003F5520.count; i++) {
        if (D_003F5520.ent[i].b == key) {
            D_003F5520.ent[i].a = 0;
            D_003F5520.ent[i].b = 0;
            D_003F5520.ent[i].sum = 0;
            return i;
        }
    }
    return -1;
}
