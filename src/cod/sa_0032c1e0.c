/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
/* NM, not registered. cygnus-2.96 (drop-reorder): Sofdec stream setup (0x32BE10)
 * and stream feed (0x32C1E0).
 * func_0032BE10: 1 insn - retail fills the delay slot of the second NULL test
 *   with an annulled lui (beql), ours uses beq.
 * func_0032C1E0: block order/tail calls differ; written before the file's
 *   drop-reorder setting was known (attempts exhausted). */


extern int func_00327830(void *sj);
extern int Obj3270_GetField_30(void *sj);
extern void Obj3270_SetField_3C(void *sj, int v);
extern void func_00328448(void *sj, int len);
extern void func_003280D8(void *sj, int sectors);
extern void func_0033F130(const char *msg);
extern void func_00329EA8();
extern void Forward33B658_33E678(void);
extern void Forward33B670_33E690(void);
extern void *func_00338B90(void *src, int mode);
extern void func_00329B60(char *self, void *sj);
extern void func_0032B660(char *self, int arg);
extern char D_00452830[];
extern char D_00452860[];

#define BSWAP32(x) ((((unsigned int)(x) >> 24) | ((x) << 24)) | ((((x) << 8) & 0xFF0000) | (((x) >> 8) & 0xFF00)))

typedef struct {
    int pad00;
    int count;
    struct {
        int offset;
        int size;
    } ent[1];
} AdxPackHdr;

__attribute__((section(".text.func_0032C1E0")))
void func_0032C1E0(char *self)
{
    void *in;
    void *out;
    int n;

    out = *(void **)(self + 8);
    in = *(void **)(self + 4);
    if (out == 0 || in == 0) {
        return;
    }
    n = func_00327830(in);
    if (*(signed char *)(self + 2) == 4) {
        func_00328448(*(void **)(self + 8), 0x7FFFFFFF);
    } else if (*(signed char *)(self + 0x6C) == 0) {
        if (Obj3270_GetField_30(*(void **)(self + 4)) >= *(int *)(self + 0xC4)) {
            Obj3270_SetField_3C(*(void **)(self + 4), -1);
        }
        func_00328448(*(void **)(self + 8), 0x7FFFFFFF);
    } else {
        func_003280D8(out, n / 2048);
    }
}

