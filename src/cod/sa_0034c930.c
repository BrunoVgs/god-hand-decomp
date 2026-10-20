/* cygnus-2.96: forwards entry idx (116-byte records at 0x1310) to func_0035C2D0 when it is idle. */
typedef struct {
    int f00;
    int busy;
    int f08[17];
    int handle;
    int pad[9];
} Entry34C;

extern int func_0035C2D0(char *self, int handle, int kind, int a, int b);

__attribute__((section(".text.func_0034C930")))
int func_0034C930(char *self, int idx, int a, int b)
{
    Entry34C *e = (Entry34C *)(self + 0x1310);

    e += idx;

    if (e->busy == 0) {
        return func_0035C2D0(self, e->handle, 11, a, b);
    }
    return 0;
}
