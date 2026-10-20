/* cygnus-2.96: func_003447A8, Sofdec header analysis: clears the header info, then (in the standby
 * state) reads the stream header and fills the info block; returns 1 on success, 0 otherwise. */
typedef struct HdrInf3447A8 {
    int stat;           /* 0x00 */
    int size;           /* 0x04 */
    char unk8[0x28];
    int ftype;          /* 0x30 */
    char unk34[0x5C];
} HdrInf3447A8;         /* 0x90 */

typedef struct Mwsf3447A8 {
    char unk0[0x78];
    int hdrsize;        /* 0x78 */
    char unk7C[0x3C];
    int ftype;          /* 0xB8 */
} Mwsf3447A8;

extern char D_004577D0[];
extern void func_003A52F0(void *p, int c, int n);
extern int GetField0OrZero_346828(Mwsf3447A8 *m);
extern void MWSFSVM_Error(const char *msg);
extern void func_003448B0(Mwsf3447A8 *m, int stat);
extern void *func_003466F8(Mwsf3447A8 *m);
extern int func_00359080(void *buf, int *size, int *hdrsize);
extern void func_00344D50(Mwsf3447A8 *m, int hdrsize);
extern void func_00344948(Mwsf3447A8 *m, int hdrsize, HdrInf3447A8 *inf);
extern void func_003448F8(Mwsf3447A8 *m, HdrInf3447A8 *inf);

__attribute__((section(".text.func_003447A8")))
int func_003447A8(Mwsf3447A8 *m, int *size, HdrInf3447A8 *inf)
{
    int hdrsize;
    int stat;
    void *buf;
    int ret;

    func_003A52F0(inf, 0, sizeof(HdrInf3447A8));
    inf->stat = 0;
    inf->size = -1;
    *size = -1;
    stat = GetField0OrZero_346828(m);
    if (stat != 1) {
        MWSFSVM_Error(D_004577D0);
        return 0;
    }
    func_003448B0(m, 2);
    buf = func_003466F8(m);
    if (buf == 0)
        return 0;
    ret = func_00359080(buf, size, &hdrsize);
    if (ret != stat)
        return ret;
    m->hdrsize = hdrsize;
    func_00344D50(m, hdrsize);
    func_00344948(m, hdrsize, inf);
    inf->size = *size;
    m->ftype = inf->ftype;
    func_003448F8(m, inf);
    return 1;
}
