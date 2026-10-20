/* ee-gcc 2.9-991111: __si_type_info_dcast, single-inheritance dynamic_cast step: matches this type or forwards
 * to the base type_info's virtual dcast through its g++ 2.x vtable entry (delta at +0x10, fn at +0x14). */
typedef struct {
    short delta;
    short index;
    void *(*fn)(char *self, void *desired, int boff, void *objptr, void *subtype, void *subptr);
} VtEntry;

extern int type_info___eq(void *a, void *b);

__attribute__((section(".text.__si_type_info_dcast")))
void *__si_type_info_dcast(char *self, void *desired, int boff, void *objptr, void *subtype, void *subptr)
{
    char *base;
    VtEntry *e;

    if (type_info___eq(self, desired))
        return objptr;
    base = *(char **)(self + 8);
    e = (VtEntry *)(*(char **)(base + 4) + 0x10);
    return e->fn(base + e->delta, desired, boff, objptr, subtype, subptr);
}
