/* cygnus-2.96: func_00346C58, fills an sfx frame request from a decoded frame: format, picture and
 * timing fields, then hands the frame back. */
typedef struct {
    char pad0[8];
    int fmt; /* 0x08 */
    char padC[0x30 - 0xC];
    int stm; /* 0x30 */
    char pad34[0x88 - 0x34];
    int f88; /* 0x88 */
    int f8C; /* 0x8C */
} MwsfdFrm;
typedef struct {
    int type; /* 0x00 */
    char pad4[0x88 - 0x4];
    int f88; /* 0x88 */
    int f8C; /* 0x8C */
    int f90; /* 0x90 */
    int f94; /* 0x94 */
} SfxReq;
extern int mwsfsfx_CnvFrmFmtTypeToSfx(int fmt);
extern void func_00346ED0(MwsfdFrm *frm, SfxReq *req);
extern int func_00346FA0(MwsfdFrm *frm, SfxReq *req);
extern void func_00346FC0(char *h, MwsfdFrm *frm, SfxReq *req);
extern void func_00347008(char *h, SfxReq *req);
extern int func_00346D80(char *h, MwsfdFrm *frm);
extern int func_00346E20(char *h, int stm);
extern void func_00346D08(char *h, MwsfdFrm *frm);

__attribute__((section(".text.func_00346C58")))
void func_00346C58(char *h, MwsfdFrm *frm, SfxReq *req)
{
    int f88;
    int f8C;

    req->type = mwsfsfx_CnvFrmFmtTypeToSfx(frm->fmt);
    func_00346ED0(frm, req);
    func_00346FA0(frm, req);
    func_00346FC0(h, frm, req);
    func_00347008(h, req);
    f88 = frm->f88;
    f8C = frm->f8C;
    req->f88 = f88;
    req->f8C = f8C;
    req->f90 = func_00346D80(h, frm);
    req->f94 = func_00346E20(h, frm->stm);
    func_00346D08(h, frm);
}
