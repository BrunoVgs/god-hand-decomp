/* sn-2.95.3-136 matched 92-byte Phase A functions. */

extern void func_003128B0(void *);
extern void func_002A9528(void *);
extern int D_00754C30;
extern int D_00754C38;
extern int D_00754C50;
extern int D_00754C58;
extern int D_00754C20;
extern int D_00754C10;
extern int func_003A50B4(void *, void *, int);
extern char D_00450E88[];
extern void func_0031C238(void *, void *, void *);
extern void func_0032ABE8(int, int, int, float);
extern int func_003244C8(void *);
extern int func_0037FD28(void *, void *);
extern void func_0031CB80(void *, void *, void *);

__attribute__((section(".text.func_0030F5F0")))
void func_0030F5F0(void)
{
    func_003128B0(&D_00754C30);
    func_003128B0(&D_00754C38);
    func_003128B0(&D_00754C50);
    func_003128B0(&D_00754C58);
    func_002A9528(&D_00754C20);
    func_002A9528(&D_00754C10);
}

__attribute__((section(".text.func_0031C1D0")))
void func_0031C1D0(void *dest, char *src)
{
    if (src == 0)
        return;
    if (func_003A50B4(src, D_00450E88, 4) != 0)
        return;
    func_0031C238(dest, src + 4, src + 0x20);
}

__attribute__((section(".text.func_003741B0")))
void func_003741B0(int *self, float scale)
{
    int object = self[0];
    if (object == 0)
        return;
    if (scale == 0.0f)
        func_0032ABE8(object, self[4], self[3], 2.0f);
    else
        func_0032ABE8(object, self[4], self[3], scale);
}

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
