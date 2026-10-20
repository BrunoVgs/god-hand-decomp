/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct {
    int pad0;
    int found; /* 0x4 */
    char pad8[0x30 - 8];
} FileInfo;
extern char D_003D9C90[];
extern char D_004542F8[];
extern char D_00454328[];
extern char D_00454350[];
extern int func_00333C00(char *name, FileInfo *info);
extern void func_00333390(char *name, char *dir);
extern void PushGlobalD8478History_331C78(int id);
extern void func_00398DA0(int a);
extern int func_00332838(FileInfo *info, char *dir);
extern void func_003260C8(char *fmt, char *dir);
extern void func_00332808(void *obj, char *msg);

__attribute__((section(".text.func_00332AE8")))
int func_00332AE8(char *name)
{
    FileInfo info;

    if (name == 0) {
        func_00332808(name, D_004542F8);
        return 0;
    }
    func_00333C00(name, &info);
    if (info.found == 0) {
        func_00333390(name, D_003D9C90);
        PushGlobalD8478History_331C78(0x8200);
        func_00398DA0(0);
        PushGlobalD8478History_331C78(0x8201);
        if (func_00332838(&info, D_003D9C90) == 0) {
            func_003260C8(D_00454328, D_003D9C90);
            func_00332808(0, D_00454350);
            return 0;
        }
    }
    return info.found;
}
