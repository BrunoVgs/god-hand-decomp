extern void func_0031CB80(void *, void *, void *);

__attribute__((section(".text.func_00380678")))
void func_00380678(void *unused, short x, short y, void *arg3, void *arg4)
{
    short rect[8];
    rect[0] = x;
    rect[1] = y;
    rect[2] = x + 0xC8;
    rect[3] = y;
    rect[4] = x;
    rect[5] = y + 8;
    rect[6] = x + 0xC8;
    rect[7] = y + 8;
    func_0031CB80(rect, arg3, arg4);
}
