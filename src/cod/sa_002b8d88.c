/* sn-2.95.3-136: NM closer handoff. */
typedef struct {
    char pad[0x1C];
    int mask[1];
} Obj2B8;

__attribute__((section(".text.func_002B8D88")))
void func_002B8D88(Obj2B8 *self, int on, int a, int b)
{
    if (on == 1) {
        self->mask[a] |= 1 << b;
        self->mask[b] |= 1 << a;
    } else {
        self->mask[a] &= ~(1 << b);
        self->mask[b] |= ~(1 << a);
    }
}
