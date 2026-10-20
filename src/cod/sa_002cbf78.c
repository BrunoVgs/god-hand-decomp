/* sn-2.95.3-136: NM closer handoff. */
typedef struct PriNode {
    int unk0;
    struct PriNode *next;
    short a;
    short b;
    unsigned int on : 1;
    unsigned int rest : 31;
    char pad10[0x24 - 0x10];
    int pri;
} PriNode;

typedef struct {
    char pad[0x1C];
    PriNode *head;
} PriList;

__attribute__((section(".text.func_002CBF78")))
PriNode *func_002CBF78(PriList *list, PriNode *skip, short a, short b, int mode, int maxPri)
{
    PriNode *best = 0;
    PriNode *n;

    for (n = list->head; n != 0; n = n->next) {
        if (n->a == a && n->b == b && n != skip) {
            switch (mode) {
            case 0:
                if (n->on != 1) {
                    return n;
                }
                break;
            case 1:
                if (n->on != 0) {
                    return n;
                }
                break;
            case 2:
                if (n->pri <= maxPri) {
                    if (best == 0 || n->pri < best->pri) {
                        best = n;
                    }
                }
                break;
            }
        }
    }
    return best;
}
