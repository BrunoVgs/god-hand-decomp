/* cygnus-2.96, -freorder-blocks dropped, as=sn: func_00350C78, decode chunks until stopped (+0x60), an error, or no more data;
 * then flush. Returns the last error. */
extern int func_00350D08(char *self, int *data, int *len, int *arg);
extern int func_003514B8(char *self, int data, int len, int arg, int *more);
extern void func_003545F8(char *self);

__attribute__((section(".text.func_00350C78")))
int func_00350C78(char *self)
{
    int data, len, arg, more;
    int r = 0;

    while (*(int *)(self + 0x60) == 0) {
        r = func_00350D08(self, &data, &len, &arg);
        if (r != 0)
            break;
        r = func_003514B8(self, data, len, arg, &more);
        if (r != 0)
            break;
        if (more == 0)
            break;
    }
    func_003545F8(self);
    return r;
}
