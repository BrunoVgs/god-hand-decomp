extern char D_005FEE00[];

__attribute__((section(".text.func_001FCCC0")))
void func_001FCCC0(char *self)
{
    if (*(short *)(self + 0x30) != 0) {
        *(short *)(self + 0x30) -= 1;
        if (*(short *)(self + 0x30) == 0) {
            unsigned int *flags = *(unsigned int **)(self + 0x28);
            *flags &= 0xFFFFFFFDU;
        }
    }
}
