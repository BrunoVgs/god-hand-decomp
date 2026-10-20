/* sn-2.95.3-136: builds the GIF packet header and 12 textured quad records. */
typedef struct {
    unsigned long rgbaq;
    unsigned long rgbaq_reg;
    int st[2];
    unsigned long st_reg;
    unsigned long f20;
    unsigned long xyz_reg0;
    int uv0[2];
    unsigned long uv0_reg;
    unsigned long f40;
    unsigned long xyz_reg1;
    int uv1[2];
    unsigned long uv1_reg;
    unsigned long f60;
    unsigned long xyz_reg2;
    float uv2[2];
    unsigned long uv2_reg;
    unsigned long f80;
    unsigned long xyz_reg3;
} Vtx15E;

typedef struct {
    unsigned long giftag0;
    int giftag1[2];
    unsigned long regs[14];
    Vtx15E v[12];
    unsigned long tail[2];
} Pkt15E;

__attribute__((section(".text.func_0015EAC8")))
void func_0015EAC8(Pkt15E *work)
{
    float one = 1.0f;
    Vtx15E *v;
    int i;

    work->giftag0 = 0x10000074;
    work->giftag1[0] = 0x11000000;
    work->giftag1[1] = 0x50000074;
    work->regs[0] = 0x102E400000008073L;
    work->regs[1] = 0xE;
    work->regs[2] = 0x8000000044L;
    work->regs[3] = 0x42;
    work->regs[4] = 0x5040C;
    work->regs[5] = 0x47;
    work->regs[7] = 8;
    work->regs[8] = 0x13A0000F8L;
    work->regs[9] = 0x4E;
    work->regs[10] = 0x2003800599422600L;
    work->regs[11] = 6;
    work->regs[12] = 0x60;
    work->regs[13] = 0x14;
    work->regs[6] = 0;
    for (i = 0; i < 12; i++) {
        v = &work->v[i];
        v->rgbaq = ((unsigned long)*(unsigned int *)&one << 32) | 0x80FFFFFF;
        v->rgbaq_reg = 1;
        v->st[0] = 0;
        v->st[1] = 0;
        v->st_reg = 2;
        ((int *)&v->uv0)[0] = 0;
        ((float *)&v->uv0)[1] = one;
        v->uv0_reg = 2;
        ((float *)&v->uv1)[0] = one;
        ((int *)&v->uv1)[1] = 0;
        v->uv1_reg = 2;
        v->uv2[0] = one;
        v->uv2[1] = one;
        v->uv2_reg = 2;
        v->xyz_reg0 = 0xD;
        v->xyz_reg1 = 0xD;
        v->xyz_reg2 = 5;
        v->xyz_reg3 = 5;
    }
    work->tail[0] = 0x3A0000F8;
    work->tail[1] = 0x4E;
}
