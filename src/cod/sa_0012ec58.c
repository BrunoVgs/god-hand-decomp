/* sn-2.95.3-136, as=sn: NM closer handoff. */
typedef struct {
    short delta;
    short index;
    void (*fn)(void *self, int flags);
} VtEntry;

typedef struct Node {
    struct Node *next;
    char pad04[0x58];
    VtEntry *vt;
} Node;

__attribute__((section(".text.func_0012EC58")))
void func_0012EC58(char *mgr, Node *obj)
{
    Node *p = *(Node **)(mgr + 0x190);
    Node *prev = 0;

    if (p == 0)
        return;
    while (obj != p) {
        prev = p;
        p = p->next;
        if (p == 0)
            return;
        __asm__ volatile("nop");
    }
    if (p == 0)
        return;
    if (p != *(Node **)(mgr + 0x190))
        prev->next = p->next;
    else
        *(Node **)(mgr + 0x190) = p->next;
    if (p != 0)
        p->vt[1].fn((char *)p + p->vt[1].delta, 3);
    *(int *)(mgr + 0x194) -= 1;
}
