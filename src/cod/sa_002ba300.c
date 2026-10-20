/* sn-2.95.3-136, as=sn: NM closer handoff. */
typedef struct PoolVEnt2BA300 {
    short delta;
    short pad;
    void *fn;
} PoolVEnt2BA300;

typedef struct PoolVtbl2BA300 {
    PoolVEnt2BA300 unk00[4];
    PoolVEnt2BA300 init;        /* 0x20 */
    PoolVEnt2BA300 unk28[2];
    PoolVEnt2BA300 setup;       /* 0x38 */
} PoolVtbl2BA300;

typedef struct PoolSlot2BA300 {
    unsigned int flags;
    struct PoolSlot2BA300 *next;
} PoolSlot2BA300;

typedef struct Pool2BA300 {
    char *slots;                /* 0x00 */
    unsigned int num;           /* 0x04 */
    int size;                   /* 0x08 */
    int unk0C;
    PoolSlot2BA300 *active;     /* 0x10 */
    int unk14;
    PoolVtbl2BA300 *vptr;       /* 0x18 */
} Pool2BA300;

__attribute__((section(".text.create")))
PoolSlot2BA300 *create(Pool2BA300 *self, int arg)
{
    unsigned int i;
    PoolSlot2BA300 *slot;
    PoolSlot2BA300 *head;
    PoolSlot2BA300 *p;

    for (i = 0; i < self->num; i++) {
        slot = (PoolSlot2BA300 *)(self->slots + self->size * i);
        if (slot->flags & 0x603) {
            continue;
        }
        ((void (*)(void *, void *, int, unsigned int))self->vptr->init.fn)(
            (char *)self + self->vptr->init.delta, slot, self->size, i);
        if (((int (*)(void *, void *, int))self->vptr->setup.fn)(
                (char *)self + self->vptr->setup.delta, slot, arg) == 0) {
            return 0;
        }
        head = self->active;
        for (p = head; p != 0; ) {
            if (p == slot) {
                goto done;
            }
            p = p->next;
            __asm__ volatile("nop");
        }
        slot->next = head;
        self->active = slot;
done:
        return slot;
    }
    return 0;
}
