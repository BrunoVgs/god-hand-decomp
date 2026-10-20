/* cygnus-2.96: MPV decode one unit from the stream joint, then skip to the next delimiter (0x36B798). */
typedef struct Sj { unsigned char *f0; int f4; } Sj;

typedef struct SjIf {
    int pad[6];
    void (*getChunk)(void *sj, int id, unsigned int len, Sj *out);   /* +0x18 */
    void (*ungetChunk)(void *sj, int id, Sj *ck);                    /* +0x1C */
    void (*putChunk)(void *sj, int id, Sj *ck);                      /* +0x20 */
} SjIf;

typedef struct SjObj { SjIf *vt; } SjObj;

extern int func_0036B888(char *h, unsigned char *p, int n);
extern void func_0033ACA0(Sj *ck, int n, Sj *a, Sj *b);
extern unsigned int MPV_GoNextDelimSj(SjObj *sj);

__attribute__((section(".text.func_0036B798")))
int func_0036B798(char *h, SjObj *sj)
{
    Sj tail;
    Sj *ck;
    unsigned char *p;
    int base;
    int bit;
    int ret;

    base = ~3;
    ck = (Sj *)(h + 0x38C);
    sj->vt->getChunk(sj, 1, 0x7FFFFFFF, ck);
    p = ck->f0;
    base &= (int)p;
    bit = ((int)p - base) * 8;
    base += 8;
    ret = func_0036B888(h, p, *(int *)(h + 0x390));
    base += bit >> 3;
    base -= 4;
    func_0033ACA0(ck, base - (int)ck->f0, ck, &tail);
    sj->vt->putChunk(sj, 0, ck);
    sj->vt->ungetChunk(sj, 1, &tail);
    MPV_GoNextDelimSj(sj);
    return ret;
}
