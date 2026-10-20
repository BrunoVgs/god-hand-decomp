extern char D_005FEE00[];
extern void func_002E0DE8(int, int, int, char *, ...);
extern char D_0045C3E0;

__attribute__((section(".text.func_00380638")))
void func_00380638(char *object)
{
    int difference = *(int *)(object + 0xC) - *(int *)(object + 8);
    func_002E0DE8(3, (short)(difference + 7), 0xC, &D_0045C3E0);
}
