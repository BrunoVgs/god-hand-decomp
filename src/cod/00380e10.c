/* sn-2.95.3-136: func_00380E10, release the ten 0x48-byte slots at +0x48. */
typedef struct {
    char pad00[0x30];
    int obj;
    int res;
} RelSlotBody;

typedef struct {
    unsigned char active;
    char pad01[0x10 - 0x01];
    RelSlotBody body;
} RelSlot;

extern void func_00329EA8(int obj);
extern void func_0032B300(int obj, void *arg);
extern void func_003298C0(int obj);
extern void func_0031C900(int res);

__attribute__((section(".text.func_00380E10")))
void func_00380E10(char *self)
{
    RelSlot *s;
    RelSlotBody *b;
    int i;

    for (i = 0; i < 10; i++) {
        s = &((RelSlot *)(self + 0x48))[i];
        b = &s->body;
        if (b->obj != 0) {
            func_00329EA8(b->obj);
            if (s->active) {
                s->active = 0;
                func_0032B300(b->obj, 0);
            }
            func_003298C0(b->obj);
            b->obj = 0;
            func_0031C900(b->res);
        }
    }
}
