/* sn-2.95.3-136: func_00375500, flush the two transfer buffers and run the sync, measuring the time
 * in hblanks (T0 counter) and microseconds and keeping the peaks. */
#include "godhand/sndSys76A790.h"

extern unsigned long GetTimerSystemTime(void);
extern void TimerBusClock2USec(unsigned long clock, unsigned int *sec, unsigned int *usec);
extern void SyncDCache(void *start, void *end);
extern void func_003758E8(int mode);
extern char D_0076A9C0[];
extern char D_0076B1C0[];

__attribute__((section(".text.func_00375500")))
void func_00375500(void)
{
    SndSys76A790 *p = &D_0076A790;
    volatile unsigned int *t0 = (volatile unsigned int *)0x10000800;
    unsigned int sec, usec;
    int start, end;
    unsigned int h0, h1;
    char *buf;

    p->unk84 = 0;
    start = GetTimerSystemTime();
    h0 = *t0;
    buf = D_0076A9C0;
    SyncDCache(buf, buf + 0x7FF);
    buf = D_0076B1C0;
    SyncDCache(buf, buf + 0x7FF);
    func_003758E8(2);
    h1 = *t0;
    end = GetTimerSystemTime();
    if (h1 < h0)
        p->hblanks = 0;
    else
        p->hblanks = h1 - h0;
    TimerBusClock2USec((unsigned int)(end - start), &sec, &usec);
    p->usec = usec;
    if (p->hblanksMax < p->hblanks)
        p->hblanksMax = p->hblanks;
    if (p->usec > p->usecMax)
        p->usecMax = p->usec;
}
