/* cygnus-2.96: ADXF file range lookup: sum the sector counts of the files before flid in the partition
 * table and return the partition, directory, sector offset and the file's size. */
typedef struct AdxfPtInfo {
    char unk00[0xF];
    signed char type;                   /* 0x0F 1 = packed 32-bit entries */
    char fname[0x100];                  /* 0x10 */
    void *dir;                          /* 0x110 */
    int ofst;                           /* 0x114 */
    int top;                            /* 0x118 also the 16-bit table base */
    int tbl[1];                         /* 0x11C */
} AdxfPtInfo;

extern AdxfPtInfo *D_003EB308[];

extern int adxf_ChkPrmGfr(int ptid, int flid);
extern int func_00324858(int ent);
extern void func_003A5DA0(char *d, char *s, int n);

__attribute__((section(".text.func_00324640")))
int func_00324640(int ptid, int flid, char *fname, void **dir, int *ofst, int *fnsct, int *fsize)
{
    AdxfPtInfo *pt;
    unsigned short *tbl16;
    int *tbl32;
    int ret;
    int ofs;
    int i;

    ret = adxf_ChkPrmGfr(ptid, flid);
    if (ret < 0) {
        *dir = 0;
        *ofst = -1;
        *fnsct = -1;
        *fsize = -1;
        return ret;
    }
    pt = D_003EB308[ptid];
    if (pt->type == 1) {
        tbl32 = pt->tbl;
        ofs = func_00324858(pt->top);
        for (i = 0; i < flid; i++)
            ofs += func_00324858(tbl32[i]);
        *fnsct = func_00324858(tbl32[flid]);
        *fsize = tbl32[flid];
    } else {
        ofs = *(unsigned short *)&pt->top;
        tbl16 = (unsigned short *)((char *)pt + 0x11A);
        for (i = 0; i < flid; i++)
            ofs += tbl16[i];
        *fnsct = tbl16[flid];
        *fsize = tbl16[flid] << 11;
    }
    func_003A5DA0(fname, pt->fname, 0x100);
    *dir = pt->dir;
    *ofst = pt->ofst + ofs;
    return ret;
}
