/* sn-2.95.3-136: func_00140718, rebuilds the item draw order with the selected item first (bright) and
 * the others dimmed, nearest-left items before the right ones. */
typedef struct IDWork140718 {
    char pad0[0x4F];
    unsigned char alpha;                /* 0x4F */
} IDWork140718;

typedef struct Item140718 {
    char data[0x50];
} Item140718;

typedef struct Menu140718 {
    char pad0[0xC0];
    Item140718 item[8];                 /* 0x0C0 */
    char pad340[0x18];
    unsigned char count;                /* 0x358 */
    char pad359[3];
    Item140718 *order[10];              /* 0x35C */
    signed char wait;                   /* 0x384 */
} Menu140718;

extern IDWork140718 *cIDBase_getIDWork(void *base, int id);

__attribute__((section(".text.func_00140718")))
void func_00140718(Menu140718 *m, int sel, int force)
{
    int i;
    int n;

    if (m->wait != 0 && force == 0)
        return;
    m->wait += 10;
    n = 1;
    m->order[0] = &m->item[sel];
    cIDBase_getIDWork(&m->item[sel], 0)->alpha = 0x80;
    for (i = sel - 1; i >= 0; i--) {
        m->order[n++] = &m->item[i];
        cIDBase_getIDWork(&m->item[i], 0)->alpha = 0x20;
    }
    for (i = sel + 1; i < m->count; i++) {
        m->order[n++] = &m->item[i];
        cIDBase_getIDWork(&m->item[i], 0)->alpha = 0x20;
    }
}
