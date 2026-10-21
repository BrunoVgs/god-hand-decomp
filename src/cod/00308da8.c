typedef struct HitRec {
    char pad0[8];
    unsigned short id;                  /* 0x8 */
    unsigned char num;                  /* 0xA */
} HitRec;

typedef struct HitKeyEnt {
    int used;
    int key;
} HitKeyEnt;

extern char D_005CAE50[];
extern int func_0012ED60(void *db, int a1, int a2, int a3, int a4, int a5, int a6, HitRec **out,
                         int max, unsigned int *count, int a10, int a11, int a12, int a13);
extern HitKeyEnt *Obj0000_Get_Field_20_Plus_A1_Shifted3_1333B8(void *db, int id);
extern int func_00308D68(int self, int key);

__attribute__((section(".text.func_00308DA8")))
int func_00308DA8(int self, int a1, int a2)
{
    HitRec *recs[8];
    unsigned int count;
    unsigned int i;
    int j;
    HitKeyEnt *base;

    if (func_0012ED60(D_005CAE50, a1, a2, 0, 0, 7, 300, recs, 8, &count, 0, 0, 0, 0) != 0) {
        for (i = 0; i < count; i++) {
            base = Obj0000_Get_Field_20_Plus_A1_Shifted3_1333B8(D_005CAE50, recs[i]->id);
            if (recs[i]->num == 0)
                return 1;
            for (j = 0; j < recs[i]->num; j++) {
                if (base[j].used == 0 && base[j].key != 0 && func_00308D68(self, base[j].key) == 0)
                    return 1;
            }
        }
    }
    return 0;
}
