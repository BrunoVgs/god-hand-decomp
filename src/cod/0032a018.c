typedef struct AdxDecHn {
    unsigned char unk0;
    unsigned char stat;
    char pad2[2];
    void *sj;
    char pad8[4];
    int unkC;
    char pad10[0x78];
    int ofs;
    char pad8C[0x18];
    int base;
    int sub;
} AdxDecHn;

extern int Obj3270_GetVia4_Obj33C8_14_7788(void *);
extern int Obj3270_GetVia4_Obj33C8_18_77E8(void *);
extern int Obj3270_GetVia4_0033CEF0_77B8(void *);
extern int Obj3270_GetField_2C(void *);
extern int Obj3260_Tramp_003383B0_D358(int);
extern int ADXT_GetNumSmplObuf(AdxDecHn *, int);

__attribute__((section(".text.func_0032A018")))
void func_0032A018(AdxDecHn *adxt, int *pos, int *rate)
{
    unsigned char stat = adxt->stat;
    int t, n, v;

    if ((unsigned int)(stat - 3) < 2) {
        *rate = Obj3270_GetVia4_Obj33C8_14_7788(adxt->sj);
        t = Obj3270_GetField_2C(adxt->sj);
        n = Obj3260_Tramp_003383B0_D358(adxt->unkC);
        *pos = t - (n - adxt->sub + ADXT_GetNumSmplObuf(adxt, 0)) + adxt->base;
    } else if ((signed char)stat == 5) {
        *pos = Obj3270_GetVia4_Obj33C8_18_77E8(adxt->sj);
        *rate = Obj3270_GetVia4_Obj33C8_14_7788(adxt->sj);
        *pos = *pos * (16 / Obj3270_GetVia4_0033CEF0_77B8(adxt->sj));
        *pos = *pos + adxt->base;
    } else {
        *pos = 0;
        *rate = 1;
    }
    v = *pos + adxt->ofs;
    if (v < 0)
        v = 0;
    *pos = v;
}
