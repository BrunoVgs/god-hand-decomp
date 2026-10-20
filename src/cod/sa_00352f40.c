typedef struct Blk352F40 {
    int w[11];
} Blk352F40;

typedef struct Work352F40 {
    char buf[0x200];
    int size;
} Work352F40;

typedef struct Mpv352F40 {
    int busy;
    int rate;
    int on;
    Blk352F40 blk;
    Work352F40 work;
} Mpv352F40;

typedef struct Sub352F40 {
    char pad0[0x3C];
    Blk352F40 blk;
} Sub352F40;

typedef struct Hn352F40 {
    char pad0[0xD30];
    Sub352F40 sub;
} Hn352F40;

typedef struct Para352F40 {
    void *src;
    int len;
    Work352F40 *w;
} Para352F40;

extern Mpv352F40 *func_003553C8(Hn352F40 *hn);
extern int func_00366960(Work352F40 *w, void *src, int len);

__attribute__((section(".text.func_00352F40")))
void func_00352F40(Hn352F40 *hn, int rate, Para352F40 *para)
{
    Mpv352F40 *m;
    Sub352F40 *sub;
    int len;
    Work352F40 *w;

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
