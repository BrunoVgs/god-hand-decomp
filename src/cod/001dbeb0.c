/* sn-2.95.3-136 matched TU. */

typedef struct {
    char pad0[0x104];
    int unk104;
    char pad108[0x250 - 0x108];
    int unk250;
} Obj;

typedef struct {
    Obj *obj;
    int state;
} Slot;

typedef struct {
    char pad0[0x2E64];
    Slot slots[52];
    char pad3004[0x3004 - 0x2E64 - 52 * 8];
    int vals[5];
} Mgr;

__attribute__((section(".text.func_001DBEB0")))
void func_001DBEB0(Mgr *m) {
    int i;
    int j;
    int *p = &m->slots[0].state;
    i = 51;
    /* Preserve loop-entry alignment without hoisting the state constant. */
    do {
loop:
        ;
    } while (0);
    (*(Obj **)((char *)p - 4))->unk250 |= 2;
    *p = 9;
    (*(Obj **)((char *)p - 4))->unk104 = 0;
    p += 2;
    if (--i >= 0) goto loop;
    for (j = 4; j >= 0; j--) {
        m->vals[j] = 0;
    }
}
