/* sn-2.95.3-136 matched TU. */

typedef struct SpdData {
    int a;
    int b;
} SpdData;




/* Motion_seq_readSpdData (assembler: sn): return the 8-byte speed record at data when kind is 1, else a zero record. */
__attribute__((section(".text.Motion_seq_readSpdData")))
SpdData Motion_seq_readSpdData(void *data, unsigned char kind)
{
    SpdData r;
    SpdData out;
    func_003A52F0(&r, 0, 8);
    if (kind == 1) {
        func_003A5148(&r, data, 8);
    }
    out = r;
    return out;
}
