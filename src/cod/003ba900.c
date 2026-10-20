/* cygnus-2.96 matched TU. */

extern void func_003B9DE0(char *a0);
extern char D_00460B48[];
extern char D_00460B70[];

__attribute__((section(".text.func_003BA900")))
void func_003BA900(int *obj, int n) {
    if (obj == 0) {
        func_003B9DE0(D_00460B48);
        return;
    }
    if (n <= 0) {
        func_003B9DE0(D_00460B70);
        return;
    }
    obj[6] = 144000 / (n * 1536) + 1;
}
