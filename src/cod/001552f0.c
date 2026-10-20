/* sn-2.95.3-136 matched TU. */

typedef struct {
    char pad[0x14];
    unsigned short count;
} Hdr;

typedef struct {
    char pad[0x20];
    int offs[1];
} Base;

typedef struct {
    Base *base;
    Hdr *hdr;
} Ctx;

__attribute__((section(".text.func_001552F0")))
int func_001552F0(char *obj, int idx) {
    Ctx ctx;
    int c;
    int n;

    ctx.base = *(Base **)(obj + 0x388);
    ctx.hdr = (Hdr *)(ctx.base->offs[idx] + (int)ctx.base);
    c = ctx.hdr->count;
    if (c % 24) {
        n = c / 24 + 1;
    } else {
        n = c / 24;
    }
    n *= 0x70;
    return n + 0x10;
}
