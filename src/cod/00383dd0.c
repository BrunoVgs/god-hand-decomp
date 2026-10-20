/* sn-2.95.3-136 matched TU. */

typedef struct {
    char pad0[4];
    unsigned char unk4;
    char pad5[0x1C - 5];
    short unk1C[5];
    short unk26[67];
    int unkAC;
} Unk00383DD0;

__attribute__((section(".text.func_00383DD0")))
int func_00383DD0(void *this, Unk00383DD0 *p, unsigned char flag) {
    short *arr;
    int i;

    arr = p->unk1C;
    if (flag) {
        arr = p->unk26;
    }
    for (i = 0; i < p->unkAC; i++) {
        if (i != p->unk4 - 1) {
            if (arr[i + 1] != arr[p->unk4]) {
                return 0;
            }
        }
    }
    return 1;
}
