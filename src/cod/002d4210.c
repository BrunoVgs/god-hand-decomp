extern char D_005FEE00[];
extern int func_00346848(void *);

__attribute__((section(".text.func_002D4210")))
int func_002D4210(char *self)
{
    void *object = *(void **)self;
    int result = 0;
    if (object != 0) {
        result = func_00346848(object);
        *(int *)(self + 0xA4) = result;
    }
    return result;
}
