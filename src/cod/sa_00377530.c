/* sn-2.95.3-136: NM closer handoff. */
extern void func_00377A28(void *self);

typedef struct Obj377530 {
    unsigned short flags;   /* 0x00 */
    char pad02[0x12];
    unsigned short mode;    /* 0x14 */
    unsigned short count;   /* 0x16 */
    char pad18[0x22];
    short wait;             /* 0x3A */
} Obj377530;

__attribute__((section(".text.func_00377530")))
void func_00377530(Obj377530 *o)
{
    unsigned short flags = o->flags;

    if (flags & 0x10) {
        if (o->wait == 0) {
            o->flags = flags & ~0x10;
            func_00377A28(o);
            return;
        }
    }
    if (flags & 2) {
        if (o->count != 0) {
            o->flags = flags | 4;
            o->mode = 2;
        }
    }
}
