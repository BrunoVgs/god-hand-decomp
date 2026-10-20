/* libgcc2: global constructor / destructor walkers (0x31DA48..). */

typedef void (*func_ptr)(void);

extern func_ptr *D_003C4080;          /* static p = __DTOR_LIST__ + 1 */
extern func_ptr D_003FC880[];         /* __CTOR_LIST__ */

__attribute__((section(".text.__do_global_dtors")))
void __do_global_dtors(void)
{
    while (*D_003C4080) {
        D_003C4080++;
        (*(D_003C4080 - 1))();
    }
}

__attribute__((section(".text.__do_global_ctors")))
void __do_global_ctors(void)
{
    do {
        unsigned long nptrs = (unsigned long)D_003FC880[0];
        unsigned i;

        if (nptrs == (unsigned long)-1) {
            for (nptrs = 0; D_003FC880[nptrs + 1] != 0; nptrs++)
                ;
        }
        for (i = nptrs; i >= 1; i--) {
            D_003FC880[i]();
        }
    } while (0);
}
