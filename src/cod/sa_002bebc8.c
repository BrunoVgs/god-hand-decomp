/* sn-2.95.3-136, as=sn: NM closer handoff. */
#include "godhand/cRoomSave.h"

extern cRoomSaveRow D_003C26C0[];
extern cRoomSaveData D_005E9CB8[ROOMSAVE_PAGE_NUM];
extern int D_00747A24;
extern void *func_003A52F0(void *, int, int);

/* Point data at the page of the given room (or clear and use the spare
 * page), remember the page index, and clear page 0 unless flag 0x04000000
 * is set. */
__attribute__((section(".text.func_002BEBC8")))
void func_002BEBC8(cRoomSave *self, unsigned short room)
{
    cRoomSaveRow *row;

    row = D_003C26C0;
    if (row->room != ROOMSAVE_NO_PAGE && row->room != room) {
        do {
            row++;
            if (row->room == ROOMSAVE_NO_PAGE) {
                break;
            }
            __asm__ volatile("nop");
        } while (row->room != room);
    }
    if (row->page == ROOMSAVE_NO_PAGE) {
        func_003A52F0(&self->spare, 0, sizeof(cRoomSaveData));
        self->data = &self->spare;
    } else {
        self->data = &D_005E9CB8[row->page];
    }
    if ((self->page = row->page) == 0 && !(D_00747A24 & 0x04000000)) {
        func_003A52F0(self->data, 0, sizeof(cRoomSaveData));
    }
}
