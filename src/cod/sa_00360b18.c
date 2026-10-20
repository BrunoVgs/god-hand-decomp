typedef struct Tm360B18 {
    volatile unsigned long count;
    volatile unsigned short last;
} Tm360B18;

extern volatile int D_003EEA78;
extern int D_003EEA7C;
extern volatile unsigned int *D_0045A270[];
extern volatile Tm360B18 D_00766CA8;
extern volatile Tm360B18 D_00766CB8;
extern Tm360B18 * volatile D_00766CC8;
extern volatile int D_00766CCC;

__attribute__((section(".text.func_00360B18")))
unsigned long func_00360B18(void)
{
    unsigned long r;
    unsigned int c;

    if (D_003EEA78 <= 0 || D_003EEA7C == -1) {
        return 0;
    }
    D_00766CCC++;
    if (D_00766CCC == 1) {
        D_00766CB8 = D_00766CA8;
        D_00766CC8 = &D_00766CB8;
        c = *D_0045A270[D_003EEA7C] & 0xFFFF;
        if (c < D_00766CA8.last) {
            D_00766CA8.count += 0x10000;
        }
        D_00766CA8.last = c;
        r = c + D_00766CA8.count;
        D_00766CC8 = &D_00766CA8;
    } else {
        c = *D_0045A270[D_003EEA7C] & 0xFFFF;
        r = c + D_00766CC8->count;
        if (c < D_00766CC8->last) {
            r += 0x10000;
        }
    }
    D_00766CCC--;
    return r;
}
