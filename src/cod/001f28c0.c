extern int cIDBase_release(void *);

__attribute__((section(".text.func_001F28C0")))
void func_001F28C0(char *self)
{
    cIDBase_release(self + 0x930);
    cIDBase_release(self + 0x10);
}
