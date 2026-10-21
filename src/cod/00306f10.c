/* sn-2.95.3-136: func_00306F10, drop a reference on a pool slot and free the node at zero. */
typedef struct PoolNode {
    struct PoolNode *next;
    int f04;
    unsigned char f08;
    unsigned char f09;
    short refs;
} PoolNode;

typedef struct {
    char pad000[0x300];
    PoolNode *slots[32];
} PoolWork;

extern void func_00306FF8(PoolWork *w, PoolNode *n);

__attribute__((section(".text.func_00306F10")))
int func_00306F10(PoolWork *w, int id)
{
    PoolNode **slots;
    PoolNode **slot;
    short n;

    if (id >= 32)
        return -1;
    slots = w->slots;
    slot = &slots[id];
    if (*slot == 0)
        return -1;
    n = --(*slot)->refs;
    if (n < 0)
        return n;
    if (n == 0) {
        func_00306FF8(w, *slot);
        *slot = 0;
    }
    return n;
}
