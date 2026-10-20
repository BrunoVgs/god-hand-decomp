/* cygnus-2.96: CRI file-system root/device path setup (0x335248..). */

#include "godhand/criFs.h"

extern void *memcpy(void *dst, const void *src, unsigned int n);

__attribute__((section(".text.func_00335248")))
void func_00335248(const char *path)
{
    if (path == 0) {
        D_003DA398[0] = 0;
        return;
    }
    if (path[0] != '/' && path[0] != '\\') {
        memcpy(D_003DA398, D_00454A00, 2);
    } else {
        D_003DA398[0] = 0;
    }
    func_003A57C4(D_003DA398, path);
}

__attribute__((section(".text.func_003352D0")))
void func_003352D0(const char *dev)
{
    if (dev == 0) {
        memcpy(D_003DA4A0, D_00454BB0, 6);
        return;
    }
    func_003A57C4(D_003DA4A0, dev);
}
