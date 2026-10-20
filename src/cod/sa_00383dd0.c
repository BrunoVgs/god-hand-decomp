/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_00383DD0, split from src/cod/batch36_nm.c by the NM closer. */
typedef struct KeyRow {
    char pad00[4];
    unsigned char key;      /* 0x04 */
    char pad05[0x17];
    short a[5];             /* 0x1C */
    short b[5];             /* 0x26 */
    char pad30[0x7C];
    int count;              /* 0xAC */
} KeyRow;

__attribute__((section(".text.func_00383DD0")))
int func_00383DD0(int unused, KeyRow *o, unsigned char which)
{
    short *p = o->a;
    int i;

    if (which)
        p = o->b;
    for (i = 0; i < o->count; i++) {
        if (i != o->key - 1 && p[i + 1] != p[o->key])
            return 0;
    }
    return 1;
}
