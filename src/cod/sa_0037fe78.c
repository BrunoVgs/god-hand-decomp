#include "godhand/menuCtl.h"

typedef struct Slot37FE78 {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    char unk14[0x20 - 0x14];
    int handle;                 /* 0x20 */
} Slot37FE78;

extern int func_0032DCD0(int handle, int a1);
extern int func_0032E118(int handle);
extern int func_0032A530(int handle);
extern int func_0032E1F0(int handle);
extern int func_0032E280(int handle);
extern int func_0032E310(int handle);
extern int func_0032A4A8(int handle);
extern int func_0032A5B8(int handle);
extern int func_0032A648(int handle);
extern void func_00381D60(FileSel *sel, Slot37FE78 *slot, FileSelWork *work);

__attribute__((section(".text.func_0037FE78")))
int func_0037FE78(FileSel *sel, FileSelWork *work)
{
    if (work->unk02[1] & 2) {
        Slot37FE78 *a = (Slot37FE78 *)((char *)work + 0xCC);
        int h = func_0032DCD0(a->handle, 0);
        if (GuardedCall_00329FD0_329F98(h) != 2)
            return 0;
        a->f00 = func_0032E118(a->handle);
        a->f04 = func_0032A530(h);
        a->f08 = func_0032E1F0(a->handle);
        a->f0C = func_0032E280(a->handle);
        a->f10 = func_0032E310(a->handle);
        func_00381D60(sel, a, work);
        return 1;
    } else {
        MenuInfo *m = (MenuInfo *)((char *)work + 0x6C);
        if (GuardedCall_00329FD0_329F98(m->handle) < 2)
            return 0;
        m->f00 = func_0032A4A8(m->handle);
        m->f04 = func_0032A530(m->handle);
        m->f08 = func_0032A5B8(m->handle);
        m->f0C = func_0032A648(m->handle);
        func_00380EB0((MenuCtl *)sel, m, (MenuList *)work);
        return 1;
    }
}
