extern void func_00381CE0(void *, void *);
extern void func_00380D68(void *, void *);

__attribute__((section(".text.func_00382F00")))
void func_00382F00(void *a0, unsigned char *a1)
{
    if (a1[3] & 1)
        func_00381CE0(a0, a1 + 0xA4);
    else
        func_00380D68(a0, a1 + 0x34);
}
