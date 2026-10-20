extern char D_005FEE00[];
extern void Esp_killByGroup(int);
extern void func_00300C00(int, int);

__attribute__((section(".text.func_00306140")))
void func_00306140(void)
{
    Esp_killByGroup(0x20);
    func_00300C00(0x20, 1);
}
