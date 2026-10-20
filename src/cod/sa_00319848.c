typedef struct { char pad[0x34]; int flags; } Sub319848;
typedef struct {
    char pad0[0x250];
    int st;
    char pad254[0x320 - 0x254];
    Sub319848 *sub;
    char pad324[0x32D - 0x324];
    unsigned char side;
} Pl319848;
typedef struct { unsigned int lo : 7; unsigned int hi : 1; } Bits319848;
typedef struct { char pad0[4]; unsigned char on; unsigned char side; char pad6[2]; int cnt; } W319848;

extern int D_00747A80;
extern int D_00747A2C;
extern W319848 D_00754C38;
extern int func_001F8AD8(void *a0, void *a1);

__attribute__((section(".text.func_00319848")))
int func_00319848(Pl319848 *p)
{
    if (!(D_00747A80 & 0x08000000)) {
        if (((Bits319848 *)((char *)&D_00747A80 - 0x53))->hi) return 0;
        if (D_00754C38.on != 0) {
            if (D_00754C38.cnt <= 0 && (p->sub->flags & 0x200)) return 1;
        } else {
            if (D_00754C38.cnt <= 0 && (((unsigned char *)p->sub)[0x35] & 1)) return 1;
        }
        if (p->side != 0) {
            if (D_00754C38.side == 0) return 1;
        } else {
            if (D_00754C38.side == 1) return 1;
        }
        if (p->st & 2) return 1;
        if (p->st & 0x10000) return 0;
        if (func_001F8AD8((char *)p + 0x260, (char *)p + 0x80) != 0)
            return (D_00747A2C & 0x04000000) > 0;
    }
    return 1;
}
