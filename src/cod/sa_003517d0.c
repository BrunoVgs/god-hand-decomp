/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct {
    int f[9];
    int valid; /* 0x24 */
    int f28; /* 0x28 */
} TimPrm;
typedef struct {
    char pad0[0x10];
    int index; /* 0x10 */
    char pad14[0x20 - 0x14];
    int hdrofs; /* 0x20 */
} SfdSeek;
typedef struct {
    char pad0[0xD98];
    TimPrm init; /* 0xD98 */
    TimPrm cur; /* 0xDC4 */
    char padDF0[0x1FB8 - 0xDF0];
    SfdSeek seek; /* 0x1FB8 */
} SfdHn;
extern int func_0034C7D0(SfdHn *hn, int index);

__attribute__((section(".text.func_003517D0")))
void func_003517D0(SfdHn *hn)
{
    SfdSeek *seek = &hn->seek;
    TimPrm *cur = &hn->cur;
    int index = seek->index;

    if (seek->hdrofs < 0)
        seek->hdrofs = func_0034C7D0(hn, index) + 4;
    if (cur->valid < 0)
        *cur = hn->init;
}
