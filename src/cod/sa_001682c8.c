/* sn-2.95.3-136 matched TU. */
#include "godhand/cSnd.h"
#include "godhand/gameWork.h"
extern cSnd D_005FEE00;
extern long cSnd_SeCall_2CB8A0(cSnd *, short, short, short, short, long, long);
typedef struct MenuSelection {
    char pad00[0x5a];
    signed char state;
    char pad5b[5];
    int action;
    char pad64[0x2d];
    signed char selection;
} MenuSelection;
/* Handle menu selection triggers and play the corresponding sound. */
__attribute__((section(".text.func_001682C8")))
void func_001682C8(MenuSelection *menu)
{
    signed char state, selection;
    state = menu->state;
    if (state == 1) {
        if ((D_007474A0.trg & 0x8000004000000UL) && menu->selection != -1) {
            cSnd_SeCall_2CB8A0(&D_005FEE00, 0, 0x15f, -1, -1, 0, 0);
            menu->selection = state;
        } else if ((D_007474A0.trg & 0x4000008000000UL) && menu->selection != -1) {
            cSnd_SeCall_2CB8A0(&D_005FEE00, 0, 0x15f, -1, -1, 0, 0);
            menu->selection = 0;
        } else if ((D_007474A0.trg & 0x1000001000000UL) && menu->selection == -1) {
            cSnd_SeCall_2CB8A0(&D_005FEE00, 0, 0x15f, -1, -1, 0, 0);
            menu->selection = 0;
        } else if (D_007474A0.trg & 0x2000002000000UL) {
            cSnd_SeCall_2CB8A0(&D_005FEE00, 0, 0x15f, -1, -1, 0, 0);
            menu->selection = -1;
        } else if (D_007474A0.trg & 0x10000000) {
            cSnd_SeCall_2CB8A0(&D_005FEE00, 0, 0x15e, -1, -1, 0, 0);
            selection = menu->selection;
            if (selection == -1) {
                menu->state = 2;
            } else if (selection >= -1) {
                if (selection < 2)
                    menu->action = 7;
            }
        } else if (D_007474A0.trg & 0x20200000) {
            cSnd_SeCall_2CB8A0(&D_005FEE00, 0, 0x161, -1, -1, 0, 0);
            menu->state = 2;
        }
    }
}
