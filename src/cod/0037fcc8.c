extern int func_003244C8(void *);
extern int func_0037FD28(void *, void *);

__attribute__((section(".text.func_0037FCC8")))
void func_0037FCC8(char *self)
{
    char *slot = self + 0x370;
    int result;
    if (func_003244C8(*(void **)(slot + 0xF4)) != 3)
        return;
    result = func_0037FD28(self, slot);
    self[2] = result != 0 ? 10 : 6;
}
