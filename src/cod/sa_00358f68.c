/* cygnus-2.96: func_00358F68, error-reports when busy, otherwise switches the current track to state 1. */
extern int Obj34D8_SetGlobalEE0B8_IfField48(char *hn);
extern int func_0034DD70(int a0, int code);
extern int func_0034CA98(char *hn, int id);
extern void func_0034CA68(char *hn, int id, int state);

__attribute__((section(".text.func_00358F68")))
int func_00358F68(char *hn)
{
    int id;

    if (Obj34D8_SetGlobalEE0B8_IfField48(hn) != 0)
        return func_0034DD70(0, 0xFF000135);
    id = *(int *)(hn + 0x1F44);
    if (func_0034CA98(hn, id) == 1)
        return 0;
    func_0034CA68(hn, id, 1);
    *(int *)(hn + 0x44) = 1;
    return 0;
}
