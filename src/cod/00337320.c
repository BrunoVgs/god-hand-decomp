/* cygnus-2.96 matched TU. */

typedef struct {
    signed char used;
    signed char pad[23];
} Entry;

extern int D_003E0708;
extern Entry D_003E0768[];

__attribute__((section(".text.func_00337320")))
Entry *func_00337320(void) {
    int i;
    Entry *e;

    e = 0;
    for (i = 0; i < D_003E0708; i++) {
        e = &D_003E0768[i];
        if (e->used == 0) {
            break;
        }
    }
    if (i == D_003E0708) {
        return 0;
    }
    e->used = 1;
    return e;
}
