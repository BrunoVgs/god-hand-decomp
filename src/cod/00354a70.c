/* cygnus-2.96: func_00354A70, initialises n 0xF0-byte stream slots, taking each slot's id from ids[]. */
#include "godhand/criStm.h"
extern void func_0035A4D0(void *p, int a);
extern void func_00354B20(void *p);

__attribute__((section(".text.func_00354A70")))
void func_00354A70(StmSlot *s, int *ids, int n)
{
    int *p;
    int cnt;

    if (n > 0) {
        p = ids;
        cnt = n;
        do {
            s->stat = 0;
            s->unk04 = 0;
            cnt--;
            func_0035A4D0(s->lock, 0);
            s->id = *p++;
            s->unk38 = 0;
            s->unk3C = 1;
            s->unk40 = 0;
            s->unk44 = 0;
            s->unk48 = 0;
            s->unk4C = 0;
            s->unk50 = 0;
            s->owner = -1;
            func_00354B20(s->que);
            s->unkE8 = 0;
            s++;
        } while (cnt != 0);
    }
}
