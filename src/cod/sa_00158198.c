/* sn-2.95.3-136: reset every part's translate/rotate/scale to the model's base pose (0x158198). */

__attribute__((section(".text.func_00158198")))
void func_00158198(char *self)
{
    unsigned char hold[0x10] __attribute__((aligned(16)));
    char *part;
    char *base;
    char *tbl;
    float *src;
    float *pos;
    float *dst;
    float x, y, z;
    int i;

    if (*(char **)(self + 0x144) != 0) {
        base = *(char **)(self + 0x280);
        i = 0;
        tbl = (char *)(*(int *)(base + 0x10) + (int)base);
        *(char **)hold = (char *)(*(int *)tbl + (int)tbl);
        part = *(char **)(self + 0x144);
        do {
            if (!(*(int *)(part + 0x154) & 1)) {
                src = (float *)(*(int *)(*(char **)hold + 4) + *(int *)hold + i * 0x10);
                if (!(*(int *)(part + 0x154) & 0x200)) {
                    pos = (float *)(part + 0xE0);
                    x = src[0];
                    y = src[1];
                    z = src[2];
                    pos[0] = x;
                    pos[1] = y;
                    pos[2] = z;
                    dst = *(float **)(part + 0xD0);
                    if (dst != pos) {
                        dst[0] = pos[0];
                        dst[1] = pos[1];
                        dst[2] = pos[2];
                    }
                }
                if (!(part[0x155] & 1)) {
                    *(float *)(part + 0x100) = *(float *)(part + 0x104) = *(float *)(part + 0x108) = 0.0f;
                }
                if (!(*(int *)(part + 0x154) & 0x400)) {
                    *(float *)(part + 0x110) = *(float *)(part + 0x114) = *(float *)(part + 0x118) = 1.0f;
                }
            }
            part = *(char **)(part + 0x144);
            i++;
        } while (part != 0);
    }
}
