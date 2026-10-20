/* cygnus-2.96: func_00354E08, takes a free stream entry, opens it into *out and records its
 * buffer range; in mode 2 also assigns it an owner id. */
#include "godhand/criStm.h"
extern void *func_003556C8(StmSys *sys);
extern void func_00354EC8(StmSys *sys, StmSlot *ent, StmBuf **out);
extern void *func_0035B678(StmSys *sys, StmBuf *buf);
extern int func_003557B0(StmSys *sys);

__attribute__((section(".text.func_00354E08")))
int func_00354E08(StmSys *sys, StmBuf **out, int *owner)
{
    StmRange *range = &sys->range;
    StmSlot *ent;
    StmBuf *buf;
    void *p;

    ent = func_003556C8(sys);
    if (ent == 0) {
        *out = 0;
        return (int)ent;
    }
    func_00354EC8(sys, ent, out);
    buf = *out;
    range->start = buf->start;
    range->size = buf->size;
    p = func_0035B678(sys, buf);
    if (p == 0) {
        *out = 0;
        return (int)p;
    }
    if (sys->mode == 2) {
        int id = func_003557B0(sys);
        ent->owner = id;
        *owner = id;
    }
    return 0;
}
