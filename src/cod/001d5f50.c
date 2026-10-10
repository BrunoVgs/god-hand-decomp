/* sn-2.95.3-136 matched TU. */

extern void CustomIDWork_SetOffsetPosY(void *work, int y);
extern void CustomIDWork_SetMoveOffsetPosY(void *work, int from, int to, int frames);
extern void SetFlagOnEntries7C_1D51B8(void *self, int entry, int on);

#define PANEL_WORK       0x105C         /* CustomIDWork of the sliding panel */
#define PANEL_Y_HIDDEN   0x46
#define PANEL_SLIDE_FRAMES  0xA

/* Panel mode: 0 hidden, 1 shown, 2 slide in, 3 slide out; entries 0x21 and 0x22 follow the mode. */
__attribute__((section(".text.PanelWork_setMode")))
void PanelWork_setMode(char *self, int mode) {
    switch (mode & 0xFFFF) {
    default:
    case 0:
        CustomIDWork_SetOffsetPosY(self + PANEL_WORK, PANEL_Y_HIDDEN);
        SetFlagOnEntries7C_1D51B8(self, 0x21, 0);
        SetFlagOnEntries7C_1D51B8(self, 0x22, 0);
        break;
    case 1:
        CustomIDWork_SetOffsetPosY(self + PANEL_WORK, 0);
        SetFlagOnEntries7C_1D51B8(self, 0x21, 0);
        SetFlagOnEntries7C_1D51B8(self, 0x22, 1);
        break;
    case 2:
        CustomIDWork_SetMoveOffsetPosY(self + PANEL_WORK, PANEL_Y_HIDDEN, 0, PANEL_SLIDE_FRAMES);
        SetFlagOnEntries7C_1D51B8(self, 0x21, 0);
        SetFlagOnEntries7C_1D51B8(self, 0x22, 1);
        break;
    case 3:
        CustomIDWork_SetMoveOffsetPosY(self + PANEL_WORK, 0, PANEL_Y_HIDDEN, PANEL_SLIDE_FRAMES);
        break;
    }
}
