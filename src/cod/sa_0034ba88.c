typedef struct Rng34BA88 {
    int pos;
    int len;
} Rng34BA88;

typedef struct Hdr34BA88 {
    int unk0;
    int size;
    Rng34BA88 rng;
    char pad10[0x18];
    int unit;
} Hdr34BA88;

typedef struct BufPtr34BA88 {
    int w[8];
} BufPtr34BA88;

extern void sfbuf_MakeBufPtr(BufPtr34BA88 *bp, Rng34BA88 *rng, int size);
extern int func_0034BC00(void *sfb, BufPtr34BA88 *bp, Rng34BA88 *rng, int idx, int n);
extern void func_0034BE00(void *sfd, void *sfb, BufPtr34BA88 *bp, Rng34BA88 *rng, int idx);
extern void func_0034BEB8(void *sfb, BufPtr34BA88 *bp, Rng34BA88 *rng, int idx);
extern void func_0034BF58(void *sfb, BufPtr34BA88 *bp, Rng34BA88 *rng, int idx);

__attribute__((section(".text.func_0034BA88")))
int func_0034BA88(void *sfd, void *sfb, Hdr34BA88 *h)
{
    BufPtr34BA88 bp;
    Rng34BA88 *rng = &h->rng;
    int r;

    sfbuf_MakeBufPtr(&bp, rng, h->size);
    r = func_0034BC00(sfb, &bp, rng, 0, rng->pos % h->unit);
    if (r != 0)
        return r;
    r = func_0034BC00(sfb, &bp, rng, 1, 0x800);
    if (r != 0)
        return r;
    r = func_0034BC00(sfb, &bp, rng, 2, 0);
    if (r != 0)
        return r;
    func_0034BE00(sfd, sfb, &bp, rng, 3);
    func_0034BEB8(sfb, &bp, rng, 4);
    func_0034BE00(sfd, sfb, &bp, rng, 5);
    func_0034BEB8(sfb, &bp, rng, 6);
    func_0034BF58(sfb, &bp, rng, 7);
    return 0;
}
