/* cygnus-2.96, -freorder-blocks dropped, as=sn: func_00343D68, starts playback of the attached movie handle
 * with func_00345848 as its callback; reports and returns -1 on failure. */
extern int func_00358968(char *mv);
extern int func_0034DE20(char *mv, int cb, int arg);
extern void func_00345848(void);
extern void func_00345750(int code);
extern void MWSFSVM_Error(char *msg);
extern void func_00343AE8(int ply);
extern char D_004573D8[];
extern char D_00457410[];

__attribute__((section(".text.func_00343D68")))
int func_00343D68(char *ply)
{
    char *mv = *(char **)(ply + 0x3C);
    *(char **)(ply + 0x3C) = 0;
    if (func_00358968(mv) != 0) {
        MWSFSVM_Error(D_004573D8);
        return -1;
    }
    *(char **)(ply + 0x3C) = mv;
    if (func_0034DE20(mv, (int)func_00345848, (int)ply) != 0) {
        func_00345750(-0x12F);
        MWSFSVM_Error(D_00457410);
        return -1;
    }
    func_00343AE8((int)ply);
    return 0;
}
