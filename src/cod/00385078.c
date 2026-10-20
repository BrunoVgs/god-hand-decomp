/* sn-2.95.3-136: menu list cursor/refresh states (0x385078..). */

#include "godhand/menuCtl.h"

extern void func_0032BDC0(int handle, int a1, int idx);
extern int func_0032A4A8(int handle);
extern int func_0032A530(int handle);
extern int func_0032A5B8(int handle);
extern int func_0032A648(int handle);

__attribute__((section(".text.func_00385078")))
void func_00385078(MenuCtl *ctl, MenuPad *pad)
{
    MenuList *list = &ctl->list;
    MenuInfo *info = &ctl->list.info;
    int r;

    if (pad->trg & 0x8000) {
        ctl->cursor = (ctl->cursor == 0 ? list->count : ctl->cursor) - 1;
    } else if (pad->trg & 0x2000) {
        if (ctl->cursor < list->count - 1) {
            ctl->cursor++;
        } else {
            ctl->cursor = 0;
        }
    } else {
        return;
    }
    r = func_00380AE8(ctl, info, list);
    if (r != 0) {
        list->result = r;
    } else {
        func_0032BDC0(info->handle, list->f84, ctl->cursor);
        ctl->state = 1;
    }
}

__attribute__((section(".text.func_00385138")))
void func_00385138(MenuCtl *ctl)
{
    MenuInfo *info = &ctl->list.info;

    if (GuardedCall_00329FD0_329F98(info->handle) < 2) {
        return;
    }
    info->f00 = func_0032A4A8(info->handle);
    info->f04 = func_0032A530(info->handle);
    info->f08 = func_0032A5B8(info->handle);
    info->f0C = func_0032A648(info->handle);
    func_00380EB0(ctl, info, &ctl->list);
    ctl->state = 0;
}
