typedef struct Sub3533A8 {
    void *dec;          /* 0x00 */
    char unk4[0x70];
    int stat;           /* 0x74 */
    char unk78[0x98];
    int active;         /* 0x110 */
} Sub3533A8;

typedef struct Frm3533A8 {
    char unk0[0x18];
    int kind;           /* 0x18 */
} Frm3533A8;

typedef struct Ply3533A8 {
    char unk0[0xE48];
    int noloop;         /* 0xE48 */
    char unkE4C[0x1174];
    Sub3533A8 *sub;     /* 0x1FC0 */
} Ply3533A8;

extern int func_0036A300(void *dec, int *eos, int *term);
extern int GetArrayElemA0C_35A1C8(Ply3533A8 *ply, int idx);

__attribute__((section(".text.func_003533A8")))
void func_003533A8(Ply3533A8 *ply, Frm3533A8 *frm, int mode)
{
    Sub3533A8 *s = ply->sub;
    void *dec = s->dec;
    int stat = s->stat;
    int eos, term;

    if (s->active != 0) {
        func_0036A300(dec, &eos, &term);
        if (eos == 1) {
            stat = 5;
        } else {
            if (ply->noloop == 0) {
                int v = GetArrayElemA0C_35A1C8(ply, 0x49);
                if (v == 1)
                    term = v;
            }
            if (term == 1)
                stat = 2;
        }
    }
    if (mode == 1) {
        if ((unsigned int)(frm->kind - 1) < 2)
            stat = 2;
    } else if (stat == 2) {
        stat = 3;
    } else if (stat == 3) {
        stat = 5;
    }
    s->stat = stat;
}
