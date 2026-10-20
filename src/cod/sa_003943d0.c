extern int func_003A5678(int a0, int a1);
extern void *D_003F852C;

struct Elem {
    int field_0;
    int field_4;
    unsigned short field_8;
    unsigned char field_A;
    unsigned char field_B;
};

struct Node_003943D0 {
    char pad[0x4];
    int field_4;
    int field_8;
    struct Elem *field_C;
    int field_10;
    char pad2[0x30 - 0x14];
    struct Node_003943D0 *field_30;
};

extern int func_00394290(int a0, int a1, int idx, int a3);

__attribute__((section(".text.func_003943D0")))
int func_003943D0(struct Elem *a0) {
    struct Node_003943D0 *node;
    struct Elem *elem;
    int cnt;
    int name;
    int val;
    unsigned short id;

    a0->field_B = 1;
    id = a0->field_8;
    val = a0->field_4;
    node = (struct Node_003943D0 *)D_003F852C;
    name = a0->field_0;
    if (node != 0) {
        do {
            cnt = node->field_10;
            elem = node->field_C;
            if (cnt != 0) {
                do {
                    if (elem->field_8 == id && func_003A5678(elem->field_0, name) == 0 &&
                        (elem->field_A == 1 || elem->field_A == 3)) {
                        if (func_00394290(node->field_4, node->field_8, elem - node->field_C, val) == 0)
                            return 0;
                        break;
                    }
                    elem++;
                } while (--cnt != 0);
            }
            node = node->field_30;
        } while (node != 0);
    }
    return 1;
}
