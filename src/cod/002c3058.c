/* sn-2.95.3-136 matched TU. */

__attribute__((section(".text.func_002C3058")))
void func_002C3058(int arg0, unsigned int *slot, unsigned int *node) {
    while (*slot != 0xFFFFFFFF) {
        if ((*slot & 0x80000000) && (unsigned int *)(*slot & 0x7FFFFFFF) == node) {
            *slot = *node;
            return;
        }
        slot = (unsigned int *)(*slot & 0x7FFFFFFF);
    }
}
