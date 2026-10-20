extern char D_003EE800[];
extern void *func_003A52F0(void *, int, int);
extern void func_00360710(int);

__attribute__((section(".text.func_0035FEA8")))
void func_0035FEA8(void)
{
    char *pointer = D_003EE800;
    func_003A52F0(pointer, 0, 0x26C);
    *(int *)(pointer + 8) = 8;
    func_00360710(0);
}
