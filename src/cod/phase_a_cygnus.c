/* cygnus-2.96 matched Phase A functions using block reordering. */

extern char D_00458848[];
extern void MWSFSVM_Error(void *);
extern void SFD_SetCond(int, int, int);
extern int func_003A5148(int, int, int);
extern char D_003EE800[];
extern int func_003A52F0(void *, int, int);
extern void func_00360710(int);
extern void *func_00348938(void *);
extern int func_00346DD0(void *, int);
extern int SUD_AnalyTypeCcs(char *, int);

__attribute__((section(".text.func_00346B78")))
void func_00346B78(int condition)
{
    if ((unsigned int)(condition + 1) >= 3)
        MWSFSVM_Error(D_00458848);
    else
        SFD_SetCond(0, 0x3D, condition);
}

__attribute__((section(".text.func_0036F008")))
void func_0036F008(char *object, void *source, int count)
{
    char *header = object + 0x14C;
    int offset = *(int *)(header + 8);
    int size = *(int *)(header + 4);
    void *base = *(void **)header;
    int remaining = size - offset;
    if (count < remaining)
        remaining = count;
    *(int *)(header + 8) = offset + remaining;
    func_003A5148((int)((char *)base + offset), (int)source, remaining);
}

__attribute__((section(".text.func_0035FEA8")))
void func_0035FEA8(void)
{
    char *pointer = D_003EE800;
    func_003A52F0(pointer, 0, 0x26C);
    *(int *)(pointer + 8) = 8;
    func_00360710(0);
}

__attribute__((section(".text.func_00354430")))
void func_00354430(int *destination, int *source)
{
    func_003A5148(destination[0], source[0], source[1]);
    __asm__ __volatile__("" : : : "$2");
    destination[1] = source[1];
}

__attribute__((section(".text.func_003483F8")))
void func_003483F8(void *key, void *argument)
{
    void *object;
    void (*method)(void *);
    object = func_00348938(key);
    if (argument == 0)
        return;
    if (object == 0)
        return;
    method = *(void (**)(void *))((char *)object + 0x10);
    if (method == 0)
        return;
    method(argument);
}

__attribute__((section(".text.func_00355408")))
void *func_00355408(char *object, void *key)
{
    char *record;
    char *slot;
    char *cursor;
    int index;
    record = *(char **)(object + 0x1FC0);
    slot = object + 0x16B0;
    cursor = record + 0x180;
    for (index = 0; index < 16; index += 1) {
        if (slot + 8 == key)
            return cursor;
        slot += 0x88;
        cursor += 0xF0;
    }
    return 0;
}

__attribute__((section(".text.func_00346D80")))
int func_00346D80(void *table, char *object)
{
    int ok;
    char *ccs;
    ok = func_00346DD0(table, *(int *)(object + 0x30)) == 1;
    ccs = *(char **)(object + 0x88);
    if (ccs != 0)
        ok = SUD_AnalyTypeCcs(ccs, *(int *)(object + 0x8C)) == 1;
    return ok;
}

