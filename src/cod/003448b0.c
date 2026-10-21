/* cygnus-2.96: set the handle's status once; a different status after that is an error. */
typedef struct MwsfdStatView {
    char pad[0x2D4];
    int stat;
} MwsfdStatView;

extern char D_00457830[];
extern void MWSFSVM_Error(char *s) __attribute__((noreturn));

__attribute__((section(".text.func_003448B0")))
void func_003448B0(MwsfdStatView *m, int stat)
{
    if (m->stat == 0)
        m->stat = stat;
    else if (m->stat != stat)
        MWSFSVM_Error(D_00457830);
}
