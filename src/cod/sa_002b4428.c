/* sn-2.95.3-136: message window camera override, saves/restores the camera block (0x2B4428). */
typedef struct CamSave2B4428 {
    int w[0xD8];
} __attribute__((aligned(16))) CamSave2B4428;

extern unsigned int D_00747A84;
extern CamSave2B4428 *D_005CAFF0;
extern CamSave2B4428 D_005E75B0;
extern void func_002B45B0(char *self);

__attribute__((section(".text.func_002B4428")))
int func_002B4428(char *self, int on, int cam)
{
    if (*(int *)(self + 0xB4) == on && *(int *)(self + 0x40) == cam) {
        return 0;
    }
    if (D_00747A84 & 0x20000000) {
        return 0;
    }
    if (on == 0) {
        func_002B45B0(self);
        *D_005CAFF0 = D_005E75B0;
    } else if (*(int *)(self + 0xB4) == 0) {
        D_005E75B0 = *D_005CAFF0;
    }
    *(int *)(self + 0x40) = cam;
    *(int *)(self + 0xB4) = on;
    return 1;
}
