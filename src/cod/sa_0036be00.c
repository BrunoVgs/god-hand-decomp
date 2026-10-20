extern char *volatile D_00766CE0;
extern char D_0045A3D0[];
extern char *D_00766D38;
extern int Obj0000_Check_D_0045A460_Magic_And_D_0045A470_Val(void);
extern void func_0036BF50(void);
extern int func_0036BF58(int);
extern void func_0036C0B0(int, int);
extern void func_00369E60(void);
extern void func_0036A378(void);
extern void func_0036BF60(char *);
extern void func_0036C038(void);
extern void func_0036C0A8(void);
extern void func_0036C628(void);

__attribute__((section(".text.func_0036BE00")))
int func_0036BE00(int a0, int a1)
{
    char *p;
    int r;

    D_00766CE0 = D_0045A3D0;
    r = Obj0000_Check_D_0045A460_Magic_And_D_0045A470_Val();
    if (r != 0) {
        if (r == (int)0xFF03FF05) {
            return r;
        }
        for (;;) {
        }
    }
    func_0036BF50();
    func_0036C0B0(a0, func_0036BF58(a1));
    p = D_00766D38;
    func_00369E60();
    func_0036A378();
    func_0036BF60(p + 0x17E0);
    func_0036C038();
    func_0036C0A8();
    func_0036C628();
    return 0;
}
