/* cygnus-2.96: func_003477A8, queues a read request of size bytes on an open stream handle,
 * counting successful requests and flagging the handle on failure. */
typedef struct {
    int pad0;
    int stat; /* 0x4 */
    char pad8[0x48 - 8];
    void *sj; /* 0x48 */
    char pad4C[0x74 - 0x4C];
    int nreq; /* 0x74 */
} SfdHn;
extern char D_00458E80[];
extern char D_00458EB0[];
extern char D_00458EE0[];
extern int GetField0OrZero_346828(SfdHn *hn);
extern void MWSFSVM_Error(char *fmt, ...);
extern int func_003355C8(void *sj, int size);

__attribute__((section(".text.func_003477A8")))
void func_003477A8(SfdHn *hn, int size)
{
    if (GetField0OrZero_346828(hn) != 1) {
        MWSFSVM_Error(D_00458E80);
        return;
    }
    if (size == 0) {
        MWSFSVM_Error(D_00458EB0);
        return;
    }
    if (func_003355C8(hn->sj, size) < 0) {
        hn->stat = 4;
        MWSFSVM_Error(D_00458EE0, size);
        return;
    }
    hn->nreq++;
}
