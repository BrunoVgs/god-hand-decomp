/* cygnus-2.96: func_00336D08, sets the decoder's output callback once the stream is running. */
typedef struct {
    char pad0[0xE8];
    void *dec;     /* 0xE8 */
    int cbfn;      /* 0xEC */
    int cbobj;     /* 0xF0 */
} StmCore;

typedef struct {
    char pad0[4];
    StmCore *core; /* 0x04 */
} StmLink;

typedef struct {
    char pad0[3];
    signed char stat; /* 0x03 */
    StmLink *link;    /* 0x04 */
} DecOutHn;

extern char D_00455308[];
extern char D_00455330[];
extern void func_0033F130(char *msg);
extern void func_00340920(void *dec);

__attribute__((section(".text.func_00336D08")))
void func_00336D08(DecOutHn *hn, int fn, int obj)
{
    StmCore *c;
    void *dec;

    if (hn == 0) {
        func_0033F130(D_00455308);
        return;
    }
    c = hn->link->core;
    dec = c->dec;
    if (hn->stat < 2 || dec == 0) {
        func_0033F130(D_00455330);
        return;
    }
    func_00340920(dec);
    c->cbfn = fn;
    c->cbobj = obj;
}
