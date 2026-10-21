/* cygnus-2.96: once the decoder reaches state 3 and neither slot has data queued, finish the stream:
 * stop, check for concatenated play, and close both slots. */
#include "godhand/criSj.h"

typedef struct MwsfdSjSlot {
    int flag;           /* 0x00 */
    int pad4[4];
    SjObj *sj;       /* 0x14 */
    int pad18[2];
} MwsfdSjSlot;

typedef struct MwsfdSjOwner {
    char pad0[0x3C];
    void *sfd;                  /* 0x3C */
    char pad40[0x70 - 0x40];
    signed char concat;         /* 0x70 */
    char pad71;
    signed char stopped;        /* 0x72 */
    char pad73[0x284 - 0x73];
    MwsfdSjSlot slot[2];         /* 0x284 */
} MwsfdSjOwner;

extern char D_004592D0[];
extern int func_00359E80(void *sfd);
extern int func_003484F0(MwsfdSjSlot *s);
extern void func_00345B38(MwsfdSjOwner *o);
extern void func_00345F48(MwsfdSjOwner *o, int mode);
extern int SFD_SetConcatPlay(void *sfd);
extern void MWSFSVM_Error(char *msg);
extern void func_00348550(MwsfdSjSlot *s, int a);

__attribute__((section(".text.func_00348E18")))
void func_00348E18(MwsfdSjOwner *o)
{
    MwsfdSjSlot *s;
    MwsfdSjSlot *first;
    int c;

    if (func_00359E80(o->sfd) != 3)
        return;
    s = &o->slot[0];
    first = s;
    if (s->flag == 1 && func_003484F0(s) != 2 && s->sj->vt->getNumData(s->sj, 1) != 0)
        return;
    s = &o->slot[1];
    if (s->flag == 1 && func_003484F0(s) != 2 && s->sj->vt->getNumData(s->sj, 1) != 0)
        return;
    func_00345B38(o);
    c = o->stopped;
    if (c == 0)
        func_00345F48(o, 0);
    c = o->concat;
    if (c == 1 && SFD_SetConcatPlay(o->sfd) != 0)
        MWSFSVM_Error(D_004592D0);
    if (o->stopped != 0)
        return;
    func_00348550(first, 0);
    func_00348550(s, 0);
}
