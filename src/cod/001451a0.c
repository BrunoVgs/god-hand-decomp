extern void *func_003A5148(void *d, const void *s, unsigned int n);

__attribute__((section(".text.func_001451A0")))
void func_001451A0(char *self, void *src)
{
    func_003A5148(self + 0x3FA, src, (unsigned int)*(short *)(self + 0x3B2));
    *(unsigned int *)(self + 0x90) |= 0x40000000U;
}
