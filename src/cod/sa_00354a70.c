/* cygnus-2.96: func_00354A70, initialises n 0xF0-byte stream slots, taking each slot's id from ids[]. */
typedef struct {
    int f0; /* 0x00 */
    int f4; /* 0x04 */
    int id; /* 0x08 */
    char lock[0x38 - 0xC]; /* 0x0C */
    int f38; /* 0x38 */
    int f3C; /* 0x3C */
    int f40; /* 0x40 */
    int f44; /* 0x44 */
    int f48; /* 0x48 */
    int f4C; /* 0x4C */
    int f50; /* 0x50 */
    int pad54;
    int f58; /* 0x58 */
    char que[0xE8 - 0x5C]; /* 0x5C */
    int fE8; /* 0xE8 */
    int padEC;
} StmSlot;
extern void func_0035A4D0(void *p, int a);
extern void func_00354B20(void *p);

__attribute__((section(".text.func_00354A70")))
void func_00354A70(StmSlot *s, int *ids, int n)
{
    int *p;
    int cnt;

    if (n > 0) {
        p = ids;
        cnt = n;
        do {
            s->f0 = 0;
            s->f4 = 0;
            cnt--;
            func_0035A4D0(s->lock, 0);
            s->id = *p++;
            s->f38 = 0;
            s->f3C = 1;
            s->f40 = 0;
            s->f44 = 0;
            s->f48 = 0;
            s->f4C = 0;
            s->f50 = 0;
            s->f58 = -1;
            func_00354B20(s->que);
            s->fE8 = 0;
            s++;
        } while (cnt != 0);
    }
}
