/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct {
    char pad0[0x58];
    unsigned int picstr; /* 0x58 */
    char pad5C[0x6C - 0x5C];
    signed char progressive; /* 0x6C */
} SfdPicInf;
extern char D_004578B8[];
extern void MWSFSVM_Error(char *msg);
extern int MWSFD_GetUsePicUsr(void);
extern int SUD_AnalyTypeDivField(void *usr, int size);

__attribute__((section(".text.func_00344C98")))
int func_00344C98(void *sfd, SfdPicInf *inf, void *usr, int size)
{
    int mode = 0;
    int use;
    unsigned int picstr;

    picstr = inf->picstr;
    if (picstr < 3) {
        if (picstr == 0)
            goto error;
    } else if (picstr == 3) {
        if (inf->progressive != 0)
            goto done;
    } else {
        goto error;
    }
    mode = 2;
    goto done;
error:
    MWSFSVM_Error(D_004578B8);
done:
    use = MWSFD_GetUsePicUsr();
    if (use == 1) {
        if (SUD_AnalyTypeDivField(usr, size) == use)
            mode = 2;
    }
    return mode;
}
