/* cygnus-2.96: Sofdec stream setup (0x32BE10) and stream feed (0x32C1E0). */

extern int func_00327830(void *sj);
extern int Obj3270_GetField_30(void *sj);
extern void Obj3270_SetField_3C(void *sj, int v);
extern void func_00328448(void *sj, int len);
extern void func_003280D8(void *sj, int sectors);

__attribute__((section(".text.func_0032C1E0")))
void func_0032C1E0(char *self)
{
    void *in;
    void *out;
    int n;

    out = *(void **)(self + 8);
    in = *(void **)(self + 4);
    if (out == 0 || in == 0) {
        return;
    }
    n = func_00327830(in);
    if (*(signed char *)(self + 2) == 4) {
        func_00328448(*(void **)(self + 8), 0x7FFFFFFF);
    } else if (*(signed char *)(self + 0x6C) == 0) {
        if (Obj3270_GetField_30(*(void **)(self + 4)) >= *(int *)(self + 0xC4)) {
            Obj3270_SetField_3C(*(void **)(self + 4), -1);
        }
        func_00328448(*(void **)(self + 8), 0x7FFFFFFF);
    } else {
        func_003280D8(out, n / 2048);
    }
}

