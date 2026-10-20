/* cygnus-2.96 (no -freorder-blocks): Sofdec picture decode helpers (0x353928..). */

#include "godhand/sftim.h"

extern int func_00356358(SftimHn *hn);
extern int func_00356C58(SftimHn *hn);
extern int func_0036C920(int a, int b, int c);
void func_00354128(SftimHn *hn, SfdFrm *ft);
extern SfdFrm *func_003555A8(SftimHn *hn);
extern void func_003556A0(SfdFrm *frm);
extern void func_00354430(SfdUsrBuf *dst, SfdUsrBuf *src);
extern void *func_003A5148(void *d, const void *s, unsigned int n);    /* memcpy */
void func_003542B8(SjObj *sj, int *type, unsigned char **ext, int *extLen);
int func_00353BD8(SftimHn *hn, SfdPicInf *pic, SfdOut *out, SfdFrm **pfrm);
void func_00353EE0(SftimHn *hn, SfdWork *work, int *x, int *y);
void func_00353F68(SftimHn *hn);
void func_00354080(SftimHn *hn, SfdFrm *ft);
void func_00354210(SftimHn *hn, SfdFrm *ft, SjObj *sj);
extern int func_00353348(SftimHn *hn, int ptype);
extern int func_00353500(SftimHn *hn, unsigned int ptype);

__attribute__((section(".text.func_00353BD8")))
int func_00353BD8(SftimHn *hn, SfdPicInf *pic, SfdOut *out, SfdFrm **pfrm)
{
    SfdWork *work = hn->work;
    SfdErr *err = &hn->errInf;
    SfdFrm *frm;

    if (work->hold != 0) {
        *pfrm = work->hold;
    } else {
        *pfrm = func_003555A8(hn);
        if (*pfrm == 0) {
            err->err = 1;
            return -1;
        }
    }
    frm = *pfrm;
    frm->pic = *pic;
    frm->decTime = work->time;
    if (hn->mode == 3) {
        int mbw;
        int mbh;
        int yw;
        int cw;
        int yofs;
        int cofs;
        int yp;
        int cp;
        unsigned char *cur;
        unsigned char *ref;

        if ((pic->picType == 1 || pic->picType == 2) && work->hold == 0) {
            func_003556A0(work->cur);
            work->cur = work->ref;
            work->ref = *pfrm;
        }
        mbw = (pic->width + 15) / 16;
        yw = (mbw * 16 + 63) / 64;
        cw = (mbw * 8 + 63) / 64;
        mbh = (pic->height + 15) / 16;
        cur = work->cur->buf;
        ref = work->ref->buf;
        yofs = yw * mbh * 1024;
        cofs = cw * mbh * 512;
        yp = yw * 64;
        cp = cw * 64;
        out->cur.yPitch = yp;
        out->cur.cPitch = cp;
        out->cur.base = cur;
        out->cur.y = cur + yofs;
        out->cur.c = cur + yofs + cofs;
        out->ref.yPitch = yp;
        out->ref.cPitch = cp;
        out->ref.base = ref;
        out->ref.y = ref + yofs;
        out->ref.c = ref + yofs + cofs;
    } else {
        SfdPlane *plane;

        if (pic->picType == 1 || pic->picType == 2) {
            work->ref = frm;
            work->curIdx ^= 1;
            work->refIdx ^= 1;
        }
        plane = work->plane;
        out->cur = plane[work->curIdx];
        out->ref = plane[work->refIdx];
    }
    out->buf = (*pfrm)->buf;
    out->pic = &(*pfrm)->pic;
    out->f28 = 0;
    out->f2C = 0;
    err->err = 0;
    return 0;
}

__attribute__((section(".text.func_00353EE0")))
void func_00353EE0(SftimHn *hn, SfdWork *work, int *x, int *y)
{
    if (hn->mode == 3) {
        switch (work->pic.picType) {
        case 1:
            break;
        case 2:
            *x = work->cur->x;
            *y = work->cur->y;
            return;
        case 3:
            *x = work->cur->x + work->ref->x;
            *y = work->cur->y + work->ref->y;
            return;
        }
    }
    *x = 0;
    *y = 0;
}

__attribute__((section(".text.func_00353F68")))
void func_00353F68(SftimHn *hn)
{
    SftimRec *rec = &hn->tim.rec[5];
    SftimRec *start = &hn->tim.rec[0];

    if (rec->valid == 0) {
        SftimTc tc = hn->tim.rec[3].tc;
        int time;
        int unit;

        if (func_00353348(hn, 3) == 0 && func_00353500(hn, 3) == 0) {
            tc.frameAdd = 0;
        }
        SFTIM_Tc2Time(&tc, &time, &unit);
        rec->tc = tc;
        rec->time = time - start->time;
        rec->unit = unit;
        rec->valid = 1;
    }
}

__attribute__((section(".text.func_00354080")))
void func_00354080(SftimHn *hn, SfdFrm *ft)
{
    ft->rec = hn->tim.rec[3];
    if (func_00356358(hn) != 0) {
        ft->count = func_00356C58(hn);
    }
    func_00354128(hn, ft);
}

__attribute__((section(".text.func_00354128")))
void func_00354128(SftimHn *hn, SfdFrm *ft)
{
    SftimWork *w = &hn->tim;
    SftimRec *rec = &ft->rec;

    ft->unit = rec->unit;
    ft->time = rec->time - hn->tim.rec[5].time + w->f164;
    ft->ptsTime = rec->time;
    ft->dispTime = rec->time + w->f164;
    if (func_00356358(hn) != 0) {
        ft->ptsTime = func_0036C920(ft->unit, (ft->count - w->f160) * 1000, D_00459920[ft->pic.rate]);
        ft->time = ft->dispTime = ft->ptsTime + w->f164;
    }
    if (w->f284 < ft->time) {
        w->f284 = ft->time;
        w->f288 = ft->unit;
    }
}

__attribute__((section(".text.func_00354210")))
void func_00354210(SftimHn *hn, SfdFrm *ft, SjObj *sj)
{
    SfdWork *work = hn->work;
    int type;
    unsigned char *ext;
    int extLen;

    if (ft->pic.picType == 1 || ft->pic.picType == 2) {
        func_00354430(&work->usr, ft->usr);
    }
    func_003542B8(sj, &type, &ext, &extLen);
    if (type == 3) {
        func_003A5148(ft->usr->buf, ext, extLen);
        ft->usr->len = extLen;
    } else {
        func_00354430(ft->usr, &work->usr);
    }
}
