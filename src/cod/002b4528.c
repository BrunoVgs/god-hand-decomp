extern char D_005FEE00[];
extern int SearchCameraData(int);
extern void func_002B4428(void *, int, int);
extern int func_002B4518(void *, int);
extern void func_002B4598(void *);

__attribute__((section(".text.func_002B4528")))
void func_002B4528(void *self, int camera)
{
    func_002B4428(self, 1, SearchCameraData(camera));
}

__attribute__((section(".text.func_002B4560")))
void func_002B4560(void *self)
{
    if (func_002B4518(self, 1))
        func_002B4598(self);
}
