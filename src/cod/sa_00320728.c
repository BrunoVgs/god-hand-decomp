typedef struct {
    unsigned int lo;
    unsigned int hi;
    int val;
} Range320728;

__attribute__((section(".text.func_00320728")))
int func_00320728(unsigned int addr, Range320728 *tbl)
{
    int best = -1;
    int i;

    if (tbl != 0) {
        for (i = 0; tbl[i].lo != 0xFFFFFFFF; i++) {
            if (addr >= tbl[i].lo && addr < tbl[i].hi) {
                if (best != -1) {
                    if (tbl[best].hi < tbl[i].hi) {
                        continue;
                    }
                    if (tbl[i].lo < tbl[best].lo) {
                        continue;
                    }
                }
                best = i;
            } else {
                if (best < 0) {
                    continue;
                }
                if (addr < tbl[i].lo) {
                    break;
                }
            }
        }
        if (best != -1) {
            return tbl[best].val;
        }
    }
    return 0;
}
