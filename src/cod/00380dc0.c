extern void func_00380E10(void *);
extern void func_00381D38(void *, void *, void *);
extern void func_00383438(void *, void *);
extern void func_00380E88(void *, void *, void *);

__attribute__((section(".text.func_00380DC0")))
void func_00380DC0(char *self)
{
    func_00380E10(self);
    func_00381D38(self, self + 0x348, self + 0x318);
    func_00383438(self, self + 0x370);
    func_00380E88(self, self + 0x484, self + 0x470);
}
