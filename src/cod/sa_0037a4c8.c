typedef struct MenuSndItem {
    char pad00[7];
    signed char kind;
    char pad08[4];
    int node;
    char pad10[0x34 - 0x10];
    int flags;
    char pad38[0x9C - 0x38];
    char nodeDesc[4];
} MenuSndItem;

extern void func_00375050(int a, int b);
extern void func_00375D98(int a, int b, int c);
extern void func_00387270(int a, int b, int c, int d);
extern void func_0037A5F0(MenuSndItem *self);
extern void func_0037A668(MenuSndItem *self);
extern int BuildSoundNode_374DF8(void *desc, int arg);

__attribute__((section(".text.func_0037A4C8")))
int func_0037A4C8(MenuSndItem *self)
{
    if (self->flags & 0x40) {
        switch (self->kind) {
        case 0:
            func_00375050(0, -1);
            break;
        case 1:
            func_00387270(-1, 0, -1, 0xF);
            break;
        case 2:
            func_00375D98(0, 0, -1);
            break;
        }
        return 1;
    }
    if (self->flags & 0x20) {
        switch (self->kind) {
        case 0:
            self->node = BuildSoundNode_374DF8(self->nodeDesc, 0);
            break;
        case 1:
            func_0037A5F0(self);
            break;
        case 2:
            func_0037A668(self);
            break;
        }
        return 1;
    }
    return 0;
}
