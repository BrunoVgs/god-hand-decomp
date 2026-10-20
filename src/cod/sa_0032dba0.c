/* cygnus-2.96: func_0032DBA0, stops a movie player handle: halts decoding and the audio side, and under the
 * lock releases an owned input stream. */
typedef struct SjObj SjObj;
typedef struct {
    void *f0[3];
    void (*destroy)(SjObj *sj); /* 0x0C */
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};
typedef struct {
    char pad0;
    signed char stat; /* 0x01 */
    char pad2[2];
    void *adx; /* 0x04 */
    void *sfd; /* 0x08 */
    char padC[0x90 - 0xC];
    SjObj *sj; /* 0x90 */
    char pad94[0x1AC - 0x94];
    int f1AC; /* 0x1AC */
    char pad1B0[0x1E0 - 0x1B0];
    int ownsj; /* 0x1E0 */
} MwPly;
extern char D_00452B20[];
extern void Obj33F8_Tramp_0033F130_FCB0(char *msg);
extern void func_0032EF00(MwPly *ply);
extern void func_003282D0(void *sfd);
extern void Obj33F8_Tramp_0033B658_FC70(void);
extern void func_0032F4A8(void *adx);
extern void Obj33F8_Tramp_0033B670_FC88(void);

__attribute__((section(".text.func_0032DBA0")))
void func_0032DBA0(MwPly *ply)
{
    SjObj *sj;

    if (ply == 0) {
        Obj33F8_Tramp_0033F130_FCB0(D_00452B20);
        return;
    }
    func_0032EF00(ply);
    if (ply->sfd != 0)
        func_003282D0(ply->sfd);
    Obj33F8_Tramp_0033B658_FC70();
    if (ply->adx != 0)
        func_0032F4A8(ply->adx);
    if (ply->ownsj == 2) {
        sj = ply->sj;
        ply->sj = 0;
        if (sj != 0)
            sj->vtbl->destroy(sj);
    }
    ply->sj = 0;
    ply->stat = 0;
    ply->f1AC = 0;
    Obj33F8_Tramp_0033B670_FC88();
}
