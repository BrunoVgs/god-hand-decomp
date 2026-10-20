extern char D_005FEE00[];
extern void func_002A58D8(void *, unsigned int);

__attribute__((section(".text.func_002A58A0")))
void func_002A58A0(char *p, int value)
{
    *(int *)(p + 0x2A060) = value;
    func_002A58D8(p, 0xFFFFFFFF);
}
