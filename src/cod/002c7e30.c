/* sn-2.95.3-136 matched TU. */

extern void func_003A5148(void *dst, void *src, int n);

typedef struct MotionQuad {
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
} MotionQuad;                           /* 8 bytes, returned in $v0 */

/* Return the 8-byte record at data when kind is 1, else a zero record. */
__attribute__((section(".text.Motion_seq_readQuadData")))
MotionQuad Motion_seq_readQuadData(void *data, unsigned char kind)
{
    MotionQuad r;
    MotionQuad out;
    func_003A52F0(&r, 0, 8);
    if (kind == 1) {
        func_003A5148(&r, data, 8);
    }
    out = r;
    return out;
}
