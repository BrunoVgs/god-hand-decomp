/* cygnus-2.96: CRI stream-joint object create, 256-entry pool of 0x40-byte objects (0x3395F8);
 * same shape as SJMEM_Create with three init arguments. */

#define SJ3_POOL_NUM  0x100

typedef struct SJ3 {
    void *vtbl;                 /* 0x00 */
    int used;                   /* 0x04 */
    void *uuid;                 /* 0x08 */
    char unk0C[0x1C - 0x0C];
    int arg0;                   /* 0x1C */
    int arg1;                   /* 0x20 */
    int arg2;                   /* 0x24 */
    char unk28[0x38 - 0x28];
    void *errFn;                /* 0x38 */
    void *errObj;               /* 0x3C */
} SJ3;

extern SJ3 D_003E3FB8[SJ3_POOL_NUM];
extern int D_003E3F80[];
extern int D_00455A50[];
extern void Forward340AE8_339438(void);
extern void func_003397C8(SJ3 *e);

__attribute__((section(".text.func_003395F8")))
SJ3 *func_003395F8(int a, int b, int c)
{
    int i;
    SJ3 *e;
    for (i = 0; i < SJ3_POOL_NUM; i++) if (D_003E3FB8[i].used == 0) break;
    e = 0;
    if (i != SJ3_POOL_NUM) {
        e = &D_003E3FB8[i];
        e->used = 1;
        e->vtbl = D_003E3F80;
        e->arg0 = a;
        e->arg1 = b;
        e->arg2 = c;
        e->uuid = D_00455A50;
        e->errFn = (void *)Forward340AE8_339438;
        e->errObj = e;
        func_003397C8(e);
    }
    return e;
}
