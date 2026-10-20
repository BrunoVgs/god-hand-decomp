typedef struct {
    short id; /* 0x00 */
    short code; /* 0x02 */
    int key; /* 0x04 */
} HistEnt;
typedef struct {
    char pad0[0x160];
    HistEnt ent[16]; /* 0x160 */
    int cur; /* 0x1E0 */
} History;

__attribute__((section(".text.func_002CBD10")))
int func_002CBD10(History *h, short id, short code, int key, short lo, short hi, int n)
{
    int idx = h->cur;
    int i = 0;
    short v;

    do {
        if (idx <= -1)
            idx += 16;
        if (key == 0 || key == h->ent[idx].key) {
            if (id == h->ent[idx].id) {
                v = h->ent[idx].code;
                if (code == v)
                    return 1;
                if (v >= lo && hi >= v && --n == -1)
                    break;
            }
        }
        i++;
    } while (idx--, i < 16);
    return 0;
}
