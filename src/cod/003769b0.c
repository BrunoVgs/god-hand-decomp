/* sn-2.95.3-136 matched TU. */

typedef struct {
    unsigned short active;
    short pad2;
    int id;
    unsigned char flags;
    char pad9[0x37];
} Entry003769B0;

extern Entry003769B0 D_0076F050[];

__attribute__((section(".text.func_003769B0")))
Entry003769B0 *func_003769B0(int id) {
    Entry003769B0 *p = D_0076F050;
    int i;

    for (i = 0; i < 0x60; i++, p++) {
        if (p->active != 0 && !(p->flags & 0x10)) {
            if (id == 0) {
                return p;
            }
            if (p->id == id) {
                return p;
            }
        }
    }
    return 0;
}
