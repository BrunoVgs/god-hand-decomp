/* cygnus-2.96: 64-bit time low-word update with carry (0x34CCB0). */

__attribute__((section(".text.func_0034CCB0")))
long func_0034CCB0(long t, unsigned int lo)
{
    unsigned int c = lo < (unsigned int)t;
    long hi = t >> 32;

    return (hi + c) << 32 | lo;
}
