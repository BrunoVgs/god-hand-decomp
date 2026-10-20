/* cygnus-2.96: func_003487C0, releases slot n of the handle's 0x20-byte slot table: when the slot was
 * active it is cleared, its stream is told to stop and the buffer goes back to the pool. */
#include "godhand/criSj.h"
typedef struct {
    char pad0[0x14];
    SjObj *sj; /* 0x14 */
    char *buf; /* 0x18 */
    char pad1C[4];
} SlotEnt;
typedef struct {
    char pad0[0x3C];
    void *pool; /* 0x3C */
    char pad40[0x284 - 0x40];
    SlotEnt slot[1]; /* 0x284 */
} SlotHn;
extern int func_00348968(SlotEnt *s);
extern void func_00348498(SlotEnt *s);
extern int func_0034E090(void *pool, char *buf, SjObj *sj, int a, int b);

__attribute__((section(".text.func_003487C0")))
void func_003487C0(SlotHn *hn, int n)
{
    SlotEnt *s = &hn->slot[n];
    void *pool = hn->pool;
    SjObj *sj = s->sj;
    char *buf = s->buf;

    if (func_00348968(s) == 1) {
        func_00348498(s);
        sj->vt->reset(sj);
        func_0034E090(pool, buf + 0xC0, sj, 0, 0);
    }
}
