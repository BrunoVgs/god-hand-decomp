#include "godhand/menuCtl.h"
/* sn-2.95.3-136 matched 84-byte Phase A functions. */

extern int GuardedCall_00329FD0_329F98(int);
extern void func_003298C0(int);
extern void func_0031C900(int);
extern int func_0032DC58(int);
extern void func_0032D6F0(int);

/* Stop a file slot's stream once it reports state 5, then free its buffer. */
__attribute__((section(".text.func_00380D68")))
void func_00380D68(int unused, SlotInfoB *slot)
{
    int buf;

    if (slot->handle == 0)
        return;
    if (GuardedCall_00329FD0_329F98(slot->handle) != 5)
        return;
    func_003298C0(slot->handle);
    buf = slot->buf;
    slot->handle = 0;
    func_0031C900(buf);
}

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
