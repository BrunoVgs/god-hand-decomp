/* sn-2.95.3-136: func_00383E40, pick the next menu step from the mode bits and the pending flags. */
typedef struct {
    char pad0[3];
    unsigned char mode;
} MenuStepState;

typedef struct {
    char pad000[0x370];
    MenuStepState st;
    char pad374[0x3D4 - 0x374];
    int pendingB;
    char pad3D8[0x434 - 0x3D8];
    int pendingA;
} MenuStep;

extern void func_00383EB0(MenuStep *self, char *ctrl);
extern void func_00383F50(MenuStep *self, char *ctrl);

__attribute__((section(".text.func_00383E40")))
void func_00383E40(MenuStep *self, char *ctrl)
{
    MenuStepState *st = &self->st;

    if (st->mode & 1) {
        if (self->pendingA != 0) {
            func_00383F50(self, ctrl);
            return;
        }
    } else if (self->pendingB != 0) {
        func_00383EB0(self, ctrl);
        return;
    }
    if (st->mode & 2)
        func_00383F50(self, ctrl);
    else
        func_00383EB0(self, ctrl);
}
