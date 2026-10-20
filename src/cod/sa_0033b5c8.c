/* cygnus-2.96, -freorder-blocks dropped: func_0033B5C8, unlock: drop the nesting count, check the releasing owner when it reaches 0,
 * then run the registered unlock callback. */
typedef struct {
    int (*fn)(int arg);
    int arg;
} Cb33B;

extern Cb33B D_007588A8;
extern volatile int D_003E9948;
extern volatile int D_003E994C;
extern char D_00455E78[];
extern void PrintfErrorReport(char *fmt, int a, int b);

__attribute__((section(".text.func_0033B5C8")))
int func_0033B5C8(int owner)
{
    int r = (int)D_007588A8.fn;

    if (r != 0) {
        D_003E9948--;
        if (D_003E9948 == 0) {
            if (D_003E994C != owner)
                PrintfErrorReport(D_00455E78, D_003E994C, owner);
            D_003E994C = 0;
        }
        r = D_007588A8.fn(D_007588A8.arg);
    }
    return r;
}
