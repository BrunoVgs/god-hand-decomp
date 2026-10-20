/* cygnus-2.96: func_00349E48, one decode step of an active movie handle. */
extern int GetArrayElemA0C_35A1C8(void *hn, int idx);
extern int func_0034AAE0(void *hn);
extern void func_00349EE8(void *hn);
extern int func_00349EF0(void *hn, int *out);
extern void func_0034A748(void *hn);
extern void func_0034A818(void *hn, int v);
extern void func_0034AB18(void *hn);
extern void func_0034ABF8(void *hn);
extern void func_00349DA0(void *hn);

__attribute__((section(".text.func_00349E48")))
int func_00349E48(void *hn)
{
    int v;
    int ret;

    ret = GetArrayElemA0C_35A1C8(hn, 6);
    if (ret == 0)
        return ret;
    if (func_0034AAE0(hn) == 1)
        return 0;
    func_00349EE8(hn);
    ret = func_00349EF0(hn, &v);
    func_0034A748(hn);
    func_0034A818(hn, v);
    func_0034AB18(hn);
    func_0034ABF8(hn);
    func_00349DA0(hn);
    return ret;
}
