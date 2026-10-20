/* sn-2.95.3-136: NM closer handoff. */
typedef struct { char pad[0x10]; int ofs; char pad2[0x0C]; } Ent31C238;
typedef struct { int n0; int o4; int n8; int oC; int n10; int o14; } Hdr31C238;
typedef struct {
    unsigned char shared;
    char pad1[3];
    char *p4;
    int n8;
    Ent31C238 *ents;
    int nents;
    char *p14;
    int n18;
} Dst31C238;

extern void *func_003A5148(void *dst, void *src, int size);

__attribute__((section(".text.func_0031C238")))
void func_0031C238(Dst31C238 *d, Hdr31C238 *h, char *base)
{
    int i;

    if (d->shared == 0) {
        d->ents = (Ent31C238 *)(base + h->o4);
        d->p4 = base + h->oC;
        d->p14 = base + h->o14;
    } else {
        func_003A5148(d->ents, base + h->o4, h->n0 << 5);
        func_003A5148(d->p4, base + h->oC, h->n8 * 12);
        func_003A5148(d->p14, base + h->o14, h->n10 * 2);
    }
    d->nents = h->n0;
    d->n8 = h->n8;
    d->n18 = h->n10;
    for (i = 0; i < d->nents; i++) {
        d->ents[i].ofs += (int)d->p14;
    }
}
