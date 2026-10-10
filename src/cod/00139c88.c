/* sn-2.95.3-136 matched TU. */

#include "godhand/cMc.h"
#include "godhand/cEvent.h"
#include "godhand/cOmBase.h"

extern unsigned int D_00747A84[];
extern cMc D_005E6900;
extern cMcTaskRef D_00752C00;
extern void func_0();
extern void cMc_DllLoad(cMc *self, int pump);
extern void cMc_DllRelease(cMc *self);
extern void cTaskWork_exit(void *task);
extern void func_002D5958(void *task, void *fn);
extern void func_0030DA08(void);
extern int D_00747A78;
extern void cCamera__calcRotation(cVec *out, void *self, void *a, void *b);
extern void func_002EC310(void *self);
extern void StoreVecFromFieldB0_2B6160(cVec *dst, void *self);

/* Memory card task body: flag the system as busy (bit 31), load the card
 * module, run its stripped log hook, release it, clear the busy bit, hand the
 * task the cleanup callback func_0030DA08 and end the task. */













__attribute__((section(".text.func_002AE8A8")))
void func_002AE8A8(void) {
    D_00747A84[1] |= 0x80000000;
    cMc_DllLoad(&D_005E6900, 0);
    func_0(cEvent_nullStr00);
    cMc_DllRelease(&D_005E6900);
    D_00747A84[1] &= 0x7FFFFFFF;
    func_002D5958(D_00752C00.task, (void *)func_0030DA08);
    cTaskWork_exit(D_00752C00.task);
}

/* Per-frame camera step: unless the system word D_00747A78 has bit 31 or bit
 * 23 set, run the state handler picked by the state word at 0x520 from a
 * copy of the 2-entry table D_0041D970 (entry layout as in the object state
 * tables: adjustment, selector, table offset), then compute the view rotation
 * into a vector and copy it to 0x220. */


typedef struct StateEntry {
    short adjust;                       /* 0x0 */
    short selector;                     /* 0x2 */
    short tableOff;                     /* 0x4 */
    short pad6;
} StateEntry;

typedef struct StateTable {
    StateEntry e[2];
} StateTable;

#define SYS_NO_CAMERA  0x800000

extern StateTable D_0041D970;



__attribute__((section(".text.func_00139C88")))
void func_00139C88(char *s1)
{
    StateTable tbl;
    cVec rot;
    char *e;
    int i8;
    int f0;
    int type;
    int arg;
    int (*fp)(int);
    long entry;
    int sys = D_00747A78;
    if (sys < 0) return;
    if ((sys & SYS_NO_CAMERA) != 0) return;
    tbl = D_0041D970;
    i8 = *(int *)(s1 + 0x520) * 8;
    e = (char *)&tbl + i8;
    type = *(short *)(e + 2);
    if (type >= 0) {
        int base = *(int *)(s1 + *(short *)(e + 4));
        entry = *(long *)(base + type * 8 - 8);
        fp = (int (*)(int))(int)(entry >> 32);
    } else {
        fp = *(int (**)(int))((char *)&tbl + i8 + 4);
    }
    f0 = tbl.e[*(int *)(s1 + 0x520)].adjust;
    if (type >= 0)
        arg = (short)entry + f0;
    else
        arg = f0;
    fp((int)(s1 + arg));
    cCamera__calcRotation(&rot, s1, s1 + 0x210, s1 + 0x200);
    cVec_copy3((cVec *)(s1 + 0x220), &rot);
}

/* Push the trail of positions: shift every point of the trail (cVec array at
 * 0x2BC, count in the signed byte 0x249) one slot back, put the object's
 * position (field B0) in slot 0 and, unless bit 24 of the flags (0x11C) is set,
 * park the height (z) of every point but the last at 65520. */


typedef struct TrailObj {
    char unk000[0x11C];
    unsigned int flags;                 /* 0x11C */
    char unk120[0x129];
    signed char count;                  /* 0x249 */
    char unk24A[0x72];
    cVec *trail;                        /* 0x2BC */
} TrailObj;

#define TRAIL_HIDE_FLAG  0x1000000
#define TRAIL_FAR        65520.0f




__attribute__((section(".text.func_002EC218")))
void func_002EC218(TrailObj *self)
{
    cVec head;
    int i;
    func_002EC310(self);
    for (i = self->count - 1; i > 0; i--)
        cVec_copy3(&self->trail[i], &self->trail[i - 1]);
    StoreVecFromFieldB0_2B6160(&head, self);
    cVec_copy3(self->trail, &head);
    if ((self->flags & TRAIL_HIDE_FLAG) == 0) {
        for (i = 0; i < self->count - 1; i++)
            self->trail[i].z = TRAIL_FAR;
    }
}
