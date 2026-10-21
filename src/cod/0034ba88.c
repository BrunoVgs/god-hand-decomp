typedef struct SfdRange {
    int pos;
    int len;
} SfdRange;

typedef struct SfdRangeHdr {
    int unk0;
    int size;
    SfdRange rng;
    char pad10[0x18];
    int unit;
} SfdRangeHdr;

typedef struct SfdBufPtr {
    int w[8];
} SfdBufPtr;

extern void sfbuf_MakeBufPtr(SfdBufPtr *bp, SfdRange *rng, int size);
extern int func_0034BC00(void *sfb, SfdBufPtr *bp, SfdRange *rng, int idx, int n);
extern void func_0034BE00(void *sfd, void *sfb, SfdBufPtr *bp, SfdRange *rng, int idx);
extern void func_0034BEB8(void *sfb, SfdBufPtr *bp, SfdRange *rng, int idx);
extern void func_0034BF58(void *sfb, SfdBufPtr *bp, SfdRange *rng, int idx);

__attribute__((section(".text.func_0034BA88")))
int func_0034BA88(void *sfd, void *sfb, SfdRangeHdr *h)
{
    SfdBufPtr bp;
    SfdRange *rng = &h->rng;
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
