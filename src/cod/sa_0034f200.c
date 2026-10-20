/* cygnus-2.96: SFD ring-buffer write and per-channel term / done checks (0x34F200..). */

#include "godhand/sftim.h"

typedef struct SfdRbSpan {
    char *ptr0;                 /* 0x00 */
    int len0;                   /* 0x04 */
    char *ptr1;                 /* 0x08 */
    int len1;                   /* 0x0C */
    int unk10;
    int tag;                    /* 0x14 */
} SfdRbSpan;

typedef struct SfdPtsReq {
    long pts;                   /* 0x00 */
    char *ptr;                  /* 0x08 */
    int len;                    /* 0x0C */
} SfdPtsReq;

typedef struct SfdUsrPts {
    long pts;                   /* 0x00 */
    int len;                    /* 0x08 */
} SfdUsrPts;

extern int func_0034C2A0(SfdWork *w, int ch, SfdRbSpan *span);
extern int func_0034C378(SfdWork *w, int ch, int len, int tag);
extern int func_003596F0(SfdWork *w, int ch);
extern int func_003593F0(SfdWork *w, int ch, SfdPtsReq *req, void *out);
extern void func_00366960(void *dst, const void *src, int n);
extern int (*D_003EE2FC)(void *obj, SfdUsrPts *pts);

__attribute__((section(".text.func_0034F200")))
int func_0034F200(SfdWork *w, int ch, char *src, int len, long pts)
{
    SfdRbSpan span;
    SfdPtsReq req;
    SfdUsrPts usr;
    char out[0x10];
    char *ptr0, *ptr1;
    int len0, tag;
    int r;

    r = func_0034C2A0(w, ch, &span);
    if (r != 0) {
        return r;
    }
    ptr0 = span.ptr0;
    len0 = span.len0;
    ptr1 = span.ptr1;
    tag = span.tag;
    if (len0 + span.len1 < len) {
        return 0;
    }
    if (ch == 1) {
        if (pts >= 0) {
            if (func_003596F0(w, 1) != 0) {
                return 0;
            }
            req.pts = pts;
            req.ptr = ptr0;
            req.len = len;
            r = func_003593F0(w, 1, &req, out);
            if (r != 0) {
                return r;
            }
        }
    } else if (ch == 2) {
        if (D_003EE2FC != 0) {
            usr.pts = pts;
            usr.len = len;
            if (D_003EE2FC((char *)w + 0x12E0, &usr) == -1) {
                return 0;
            }
        }
    }
    if (len0 >= len) {
        func_00366960(ptr0, src, len);
    } else {
        func_00366960(ptr0, src, len0);
        func_00366960(ptr1, src + len0, len - len0);
    }
    r = func_0034C378(w, ch, len, tag);
    return r == 0 ? 1 : r;
}

extern void func_0034CA68(SfdWork *w, int ch, int flag);
extern int func_0034CA98(SfdWork *w, int ch);
extern void func_00356988(SfdWork *w, int a1);

__attribute__((section(".text.func_0034F390")))
void func_0034F390(SfdWork *w, int a1)
{
    SfdChIds *ch = &w->ch;

    if (ch->video != SFD_CH_NONE) {
        func_0034CA68(w, ch->video, 1);
    }
    if (ch->audio != SFD_CH_NONE) {
        func_0034CA68(w, ch->audio, 1);
    }
    if (ch->other != SFD_CH_NONE) {
        func_0034CA68(w, ch->other, 1);
    }
    func_00356988(w, a1);
}

__attribute__((section(".text.func_0034F418")))
int func_0034F418(SfdWork *w)
{
    SfdChIds *ch = &w->ch;
    int done = 1;

    if (ch->video != SFD_CH_NONE) {
        done = func_0034CA98(w, ch->video) & 1;
    }
    if (ch->audio != SFD_CH_NONE) {
        done &= func_0034CA98(w, ch->audio);
    }
    if (ch->other != SFD_CH_NONE) {
        done &= func_0034CA98(w, ch->other);
    }
    return done;
}
