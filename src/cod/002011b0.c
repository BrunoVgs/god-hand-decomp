/* sn-2.95.3-136 matched TU. */

extern void cDvd_step(void *a0);

/* sn-2.95.3-136 matched TU. */



__attribute__((section(".text.func_002011B0")))
void func_002011B0(void *a0) {
    while (*(int *)a0) {
        cDvd_step(a0);
    }
}
