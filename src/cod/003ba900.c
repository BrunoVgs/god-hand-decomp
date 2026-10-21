/* cygnus-2.96: sets the block count from the rate (144000 / (n * 0x600) + 1), error trap on NULL or n <= 0. */
extern void func_003B9DE0(int msg);
extern char D_00460B48[];
extern char D_00460B70[];

__attribute__((section(".text.func_003BA900")))
void func_003BA900(char *a0, int n) {
    if (a0 == 0) {
        func_003B9DE0((int)D_00460B48);
    } else if (n <= 0) {
        func_003B9DE0((int)D_00460B70);
    } else {
        *(int *)(a0 + 0x18) = 144000 / (n * 0x600) + 1;
    }
}
