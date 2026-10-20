/* sn-2.95.3-136: look up an entry by name and id across the registered tables; 0 if absent. */
extern int func_003A5678(int a0, int a1);
extern void *D_003F852C;

struct Elem {
    int field_0;
    int field_4;
    unsigned short field_8;
    unsigned char field_A;
    unsigned char field_B;
};

struct Node_00394290 {
    char pad[0xC];
    struct Elem *field_C;
    int field_10;
    char pad2[0x30 - 0x14];
    struct Node_00394290 *field_30;
};

__attribute__((section(".text.func_00393FD8")))
int func_00393FD8(int name, unsigned short id) {
    struct Node_00394290 *node;
    struct Elem *elem;
    int cnt;
    node = (struct Node_00394290 *)D_003F852C;
    if (node != 0) {
        do {
            cnt = node->field_10;
            elem = node->field_C;
            if (cnt != 0) {
                do {
                    if (elem->field_B != 0 && elem->field_8 == id &&
                        func_003A5678(elem->field_0, name) == 0) {
                        return elem->field_4;
                    }
                    elem++;
                } while (--cnt != 0);
            }
            node = node->field_30;
        } while (node != 0);
    }
    return 0;
}
