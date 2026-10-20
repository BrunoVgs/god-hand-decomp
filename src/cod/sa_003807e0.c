/* SN ProDG ee-gcc 2.95.3: func_003807E0, index of the table entry nearest to x in the ascending 128-entry
 * table D_003F2060 (rounds down below the midpoint), -1 past the end. */
extern unsigned short D_003F2060[];

__attribute__((section(".text.func_003807E0")))
int func_003807E0(void *a0, short x)
{
    short i;

    for (i = 0; i < 0x80; i++) {
        short v = D_003F2060[i];
        unsigned short u = D_003F2060[i];

        if (x == v)
            return i;
        if (x < v) {
            if (x < (short)(u - ((short)(u - D_003F2060[i - 1]) >> 1)))
                return (short)(i - 1);
            return i;
        }
    }
    return -1;
}
