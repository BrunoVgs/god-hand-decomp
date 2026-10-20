typedef struct MpvBlk {
    int w[11];
} MpvBlk;

typedef struct MpvWork {
    char buf[0x200];
    int size;
} MpvWork;

typedef struct MpvDec {
    int busy;
    int rate;
    int on;
    MpvBlk blk;
    MpvWork work;
} MpvDec;

typedef struct MpvSub {
    char pad0[0x3C];
    MpvBlk blk;
} MpvSub;

typedef struct MpvHn {
    char pad0[0xD30];
    MpvSub sub;
} MpvHn;

typedef struct MpvPara {
    void *src;
    int len;
    MpvWork *w;
} MpvPara;

extern MpvDec *func_003553C8(MpvHn *hn);
extern int func_00366960(MpvWork *w, void *src, int len);

__attribute__((section(".text.func_00352F40")))
void func_00352F40(MpvHn *hn, int rate, MpvPara *para)
{
    MpvDec *m;
    MpvSub *sub;
    int len;
    MpvWork *w;

    m = func_003553C8(hn);
    if (m == 0 || m->busy != 0)
        return;
    len = para->len;
    if (len > 0x200)
        len = 0x200;
    w = &m->work;
    w->size = len;
    sub = &hn->sub;
    func_00366960(w, para->src, len);
    if (rate == 0x3FFFF) {
        m->rate = 0;
        m->on = 0;
    } else {
        m->on = 1;
        m->rate = rate * 50;
    }
    m->blk = sub->blk;
    m->busy = 1;
}
