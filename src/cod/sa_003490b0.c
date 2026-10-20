/* cygnus-2.96: func_003490B0, per-frame server step of an mwsfd handle: stops a pending decode, kicks
 * the next one when idle, and flags the end status. */
typedef struct {
    int pad0;
    int stat; /* 0x04 */
    char pad8[0x3C - 0x8];
    void *sfd; /* 0x3C */
    char pad40[0x48 - 0x40];
    void *adxt; /* 0x48 */
    char pad4C[0x70 - 0x4C];
    signed char busy; /* 0x70 */
    signed char stopreq; /* 0x71 */
} MwsfdHn;
extern char D_00459330[];
extern int func_00335B08(void *adxt);
extern int func_00358F68(void *sfd);
extern void func_00346158(MwsfdHn *hn);
extern int func_00359E80(void *sfd);
extern void MWSFSVM_Error(const char *msg);

__attribute__((section(".text.func_003490B0")))
void func_003490B0(MwsfdHn *hn)
{
    void *sfd = hn->sfd;

    if (hn->stopreq == 1 && func_00335B08(hn->adxt) == 0) {
        if (func_00358F68(sfd) != 0)
            MWSFSVM_Error(D_00459330);
        hn->stopreq = 0;
    }
    if (*(unsigned short *)&hn->busy == 0 && func_00335B08(hn->adxt) == 0)
        func_00346158(hn);
    if (func_00359E80(sfd) == 6)
        hn->stat = 3;
}
