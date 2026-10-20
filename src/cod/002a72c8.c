extern char D_005FEE00[];
extern char D_005CAC90[];
extern char D_005CAE50[];
extern void *func_002A5AD0(char *);
extern void *func_0012E5C8(void *);

__attribute__((section(".text.func_002A72C8")))
void func_002A72C8(int init, int priority)
{
    if (priority == 0xFFFF && init) {
        func_002A5AD0(D_005CAC90);
        func_0012E5C8(D_005CAE50);
    }
}
