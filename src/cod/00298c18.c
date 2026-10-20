extern void displayScrollLayer(int, int);

__attribute__((section(".text.func_00298C18")))
void func_00298C18(int mode)
{
    if (mode == 3)
        displayScrollLayer(0x16, 0);
    else
        displayScrollLayer(0x16, 1);
}
