/* sn-2.95.3-136, as=sn (ps2eeas keeps the mtc1 hazard nops): 30-frame Y-rotation shake around a saved yaw. */
typedef struct {
    char pad000[0x104];
    float rotY;
    char pad108[0x2F4 - 0x108];
    unsigned char step;
    unsigned char state;
    char pad2F6[0x63C - 0x2F6];
    unsigned int timer;
    float baseRotY;
} Shaker;

__attribute__((section(".text.func_001B4460")))
void func_001B4460(Shaker *self)
{
    switch (self->state) {
    case 0:
        self->timer = 30;
        self->baseRotY = self->rotY;
        self->state = 1;
    case 1:
        if (self->timer != 0) {
            self->rotY = self->baseRotY + (float)(self->timer & 1) * 0.06981317f;
            self->timer--;
            return;
        }
        self->state = 2;
        return;
    case 2:
        self->step = self->state;
        self->rotY = self->baseRotY;
        self->state = 0;
        return;
    }
}
