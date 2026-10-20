extern int cIDBase_initialize(void *, int, int);

__attribute__((section(".text.func_0013ECF0")))
int func_0013ECF0(char *p)
{
    int result = cIDBase_initialize(p, 1, 2);
    *(short *)(p + 0xBE) = -1;
    return result;
}
