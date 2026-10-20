/* cygnus-2.96 80-byte function that needs the original block order.
 * The empty do-while keeps the error report from collapsing into a tail call. */

extern int D_003E0710;
extern int D_003E0708;
extern char D_004557C8[];
extern void func_003260C8(char *, int);

__attribute__((section(".text.func_00338848")))
void func_00338848(void *unused, int bitsPerSample)
{
    if ((D_003E0710 != 1 || D_003E0708 > 0) && bitsPerSample != 0x10) {
        func_003260C8(D_004557C8, bitsPerSample);
        do { } while (0);
    }
}
