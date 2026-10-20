/* sn-2.95.3-136: func_003127B0, create a pointer vector on the game heap and reserve n slots. */
extern void *EnsureInitThenForward_2A9538_30EE08(int size, int align, void *region);
extern void *func_003A51F4(void *d, const void *s, unsigned int n);
extern void cHeap_free(int heap, void *p);
extern void *D_003C3CF0;

typedef struct Alloc3127B0 {
    unsigned char c;
} Alloc3127B0;

typedef struct Vec3127B0 {
    Alloc3127B0 a;
    void **begin;
    void **end;
    void **cap;
} Vec3127B0;

__attribute__((section(".text.func_003127B0")))
void func_003127B0(Vec3127B0 **out, unsigned int n)
{
    Vec3127B0 *v;
    void **nb;
    void **old;
    int used;
    unsigned char al;
    volatile unsigned char save;

    v = (Vec3127B0 *)EnsureInitThenForward_2A9538_30EE08(0x10, 0x10, D_003C3CF0);
    /* The allocator byte round-trip is what retail's empty-allocator copy compiled to. */
    if (v != 0) {
        save = v->a.c;
        v->a.c = al;
        v->a.c = save;
        v->begin = 0;
        v->end = 0;
        v->cap = 0;
    }
    *out = v;
    if ((unsigned int)(v->cap - v->begin) < n) {
        old = v->begin;
        used = v->end - old;
        nb = (void **)EnsureInitThenForward_2A9538_30EE08(n * 4, 0x10, D_003C3CF0);
        func_003A51F4(nb, old, used * 4);
        if (v->begin != 0)
            cHeap_free(((int *)v->begin)[-8], v->begin);
        v->end = nb + used;
        v->begin = nb;
        v->cap = nb + n;
    }
}
