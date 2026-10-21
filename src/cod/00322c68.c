/* cygnus-2.96: ADXF load start: check the arguments, open the file by name or by partition and index,
 * fill the load record and start ADXF_ReadNw. */
typedef struct {
    int f0;
    int f4;
    int f8;
    char fC;
    char fD;
    char fE;
    char fF;
    char name[0x100];
    int f110;
    int f114;
    int f118;
} AdxfLd;

extern void func_0033F130(char *);
extern void func_00323AA0(int);
extern int adxf_ChkPrmPt(int, AdxfLd *);
extern void *func_003A52F0(void *, int, int);
extern int func_00323960(int, int);
extern int func_00324640(int, int, char *, int *, int *, int *, int *);
extern int func_00323780(int, int, int, int);
extern void func_003A5DA0(char *, int, int);
extern int ADXF_ReadNw(int, int, int);

extern int D_003EB834;
extern int D_003EB838;
extern int D_003EB83C;
extern int D_003EB840;
extern unsigned int D_003EB308[];
extern int D_003C5298;
extern int D_003C529C;
extern char D_004513F8[];
extern char D_00451438[];
extern char D_00451468[];
extern char D_00451490[];
extern char D_004514C0[];

__attribute__((section(".text.func_00322C68")))
int func_00322C68(int id, int a1, int a2, int a3, int a4, int a5, int a6, AdxfLd *w, int a8, int a9, int a10)
{
    int x4, x8, xC;
    int r;
    int n;

    if (D_003EB840 == 2) {
        func_0033F130(D_004513F8);
        return -1;
    }
    if (D_003EB838) {
        func_00323AA0(D_003EB838);
        D_003EB838 = 0;
    }
    D_003EB83C = -1;
    D_003EB840 = 1;
    if (a8 == 0) {
        func_0033F130(D_00451438);
        D_003EB840 = 4;
        return -3;
    }
    if (a9 <= 0) {
        func_0033F130(D_00451468);
        D_003EB840 = 4;
        return -3;
    }
    r = adxf_ChkPrmPt(id, w);
    if (r < 0) {
        D_003EB840 = 4;
        return r;
    }
    if (D_003EB83C >= 0) {
        func_0033F130(D_00451490);
        D_003EB840 = 4;
        return -1;
    }
    D_003EB840 = 2;
    D_003EB83C = id;
    D_003EB834 = 0;
    func_003A52F0(w, 0, 0x11C);
    D_003EB308[id] = (unsigned int)w;
    w->f0 = 0;
    if (a3 == 0) {
        D_003EB838 = func_00323960(a1, a2);
        if (D_003EB838 == 0) {
            func_0033F130(D_004514C0);
            D_003EB840 = 4;
            return -1;
        }
        r = func_00324640(a1, a2, w->name, &a4, &x4, &x8, &xC);
        if (r < 0) {
            D_003EB840 = 4;
            return r;
        }
        w->f114 = x4;
    } else {
        D_003EB838 = func_00323780(a3, a4, a5, a6);
        if (D_003EB838 == 0) {
            func_0033F130(D_004514C0);
            D_003EB840 = 4;
            return -1;
        }
        func_003A5DA0(w->name, a3, 0x100);
        w->f114 = a5;
    }
    w->fE = 0;
    w->fF = a10;
    n = a9 / 2048;
    w->f110 = a4;
    D_003C5298 = a8;
    D_003C529C = n;
    r = ADXF_ReadNw(D_003EB838, n, a8);
    if (r < 0) {
        func_00323AA0(D_003EB838);
        D_003EB840 = 4;
        return r;
    }
    w->f8 = 0;
    return 0;
}
