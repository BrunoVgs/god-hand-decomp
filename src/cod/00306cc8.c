extern int func_00306A08(void *, void *, void *);

__attribute__((section(".text.func_00306CC8")))
int func_00306CC8(
    void **table, unsigned int index, void *argument, int *output)
{
    void **slot;
    *output = 0;
    if (index >= 0x40)
        return 0;
    slot = table + index;
    if (*slot == 0)
        return 0;
    return func_00306A08(*slot, argument, output) != 0;
}
