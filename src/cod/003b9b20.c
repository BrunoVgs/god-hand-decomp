/* cygnus-2.96: func_003B9B20, shuts the stream's decoder down (under the lock) and resets the object. */
extern void func_00329EA8(char *obj);
extern void Forward33B658_325C60(void);
extern void func_003BA058(int dec);
extern void func_003B9FD0(int dec);
extern void Forward33B670_325C78(void);
extern void Obj3260_TrampVia0C_00337B30_D220(char *obj, int a1);
extern void Obj3260_TrampVia0C_00337BC8_D250(char *obj);
extern void func_003B9E60(void);

__attribute__((section(".text.func_003B9B20")))
void func_003B9B20(char *obj)
{
    char *st;
    int dec;

    func_00329EA8(obj);
    st = *(char **)(*(char **)(obj + 4) + 4);
    dec = *(int *)(st + 0xC0);
    if (dec == 0)
        return;
    Forward33B658_325C60();
    func_003BA058(dec);
    func_003B9FD0(dec);
    *(int *)(st + 0xC0) = 0;
    Forward33B670_325C78();
    Obj3260_TrampVia0C_00337B30_D220(obj, 0);
    Obj3260_TrampVia0C_00337BC8_D250(obj);
    func_003B9E60();
}
