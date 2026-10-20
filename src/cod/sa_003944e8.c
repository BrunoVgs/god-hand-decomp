/* sn-2.95.3-136: is the element registered with kind 2 or 4? Stale entries of other kinds are deactivated
 * and the lookup falls back to func_003943D0. */
extern int func_003A5678(int a0, int a1);
extern void *D_003F852C;
struct Elem;
extern int func_003943D0(struct Elem *a0);

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

__attribute__((section(".text.func_003944E8")))
int func_003944E8(struct Elem *a0) {
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
                    if (elem->field_B != 0 && elem->field_8 == a0->field_8 &&
                        func_003A5678(elem->field_0, a0->field_0) == 0) {
                        if (elem->field_A == 2 || elem->field_A == 4) {
                            return 1;
                        }
                        elem->field_B = 0;
                        goto fallback;
                    }
                    elem++;
                } while (--cnt != 0);
            }
            node = node->field_30;
        } while (node != 0);
    }
fallback:
    return func_003943D0(a0);
}
