extern void func_002A9528(void *);
extern int D_00754200;
extern int D_00754210;
extern int D_00754220;
extern int D_00754230;
extern int D_00754240;

__attribute__((section(".text.func_0030EE68")))
void func_0030EE68(int init, int priority)
{
    if (priority == 0xFFFF && init != 0) {
        func_002A9528(&D_00754200);
        func_002A9528(&D_00754210);
        func_002A9528(&D_00754220);
        func_002A9528(&D_00754230);
        func_002A9528(&D_00754240);
    }
}
