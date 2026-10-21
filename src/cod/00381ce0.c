#include "godhand/menuCtl.h"

extern void func_0031C900(int);
extern int func_0032DC58(int);
extern void func_0032D6F0(int);

__attribute__((section(".text.func_00381CE0")))
void func_00381CE0(int unused, SlotInfoA *slot)
{
    int buf;

    if (slot->handle == 0)
        return;
    if (func_0032DC58(slot->handle) != 5)
        return;
    func_0032D6F0(slot->handle);
    buf = slot->buf;
    slot->handle = 0;
    func_0031C900(buf);
}
