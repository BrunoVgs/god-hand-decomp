/* sn-2.95.3-136 matched TU. */

typedef struct {
    unsigned short unk0;
    char pad2[3];
    unsigned char unk5;
    unsigned short unk6;
    char pad8[0x48];
} Ent0037D9B0;

extern Ent0037D9B0 D_0076CF20[51];

__attribute__((section(".text.func_0037D9B0")))
void func_0037D9B0(unsigned char mask, unsigned short mode) {
    Ent0037D9B0 *p;
    int i;

    for (i = 0; i < 51; i++) {
        p = &D_0076CF20[i];
        if (p->unk0 != 0 && (p->unk5 & mask)) {
            switch (mode) {
            case 1:
                p->unk6 |= 9;
                break;
            case 2:
                p->unk6 |= 10;
                break;
            }
        }
    }
}
