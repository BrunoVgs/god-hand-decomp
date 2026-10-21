extern int setMotionInfo(void *a0, int a1, int a2, int a3, float f12, float f13, int t0);
extern int moveMotion(char *a0);

__attribute__((section(".text.func_001582A0")))
void func_001582A0(char *self, int a1, int a2, int a3, float f12, float f13, unsigned short t0)
{
    if (*(int *)(self + 0x428) != a1 || *(int *)(self + 0x42C) != a2 ||
        *(float *)(self + 0x440) != ((t0 & 4) ? -f12 : f12)) {
        setMotionInfo(self, a1, a2, a3, f12, f13, t0);
    }
    moveMotion(self);
}

