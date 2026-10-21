/* cygnus-2.96: func_003487C0, releases slot n of the handle's 0x20-byte slot table: when the slot was
 * active it is cleared, its stream is told to stop and the buffer goes back to the pool. */
#include "godhand/mwsfd.h"
#include "godhand/criSj.h"
extern int func_00348968(MwsfdSlot *slot);
extern void func_00348498(MwsfdSlot *slot);
extern int func_0034E090(void *sfd, char *buf, SjObj *sj, int a, int b);

__attribute__((section(".text.func_003487C0")))
void func_003487C0(MwsfdHn *hn, int n)
{
    MwsfdSlot *s = &hn->slot[n];
    void *sfd = hn->sfd;
    SjObj *sj = s->sj;
    char *buf = s->buf;

    if (func_00348968(s) == 1) {
        func_00348498(s);
        sj->vt->reset(sj);
        func_0034E090(sfd, buf + 0xC0, sj, 0, 0);
    }
}
