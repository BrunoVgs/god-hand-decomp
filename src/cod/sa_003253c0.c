/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
struct ThreadParam {
    int status;
    void *entry;
    void *stack;
    int stackSize;
    void *gpReg;
    int initPriority;
    int currentPriority;
    unsigned int attr;
    unsigned int option;
    int waitType;
    int waitId;
    int wakeupCount;
};

extern volatile int D_003C8138;
extern int D_003C80B4;
extern int D_003CF9D8;
extern char D_003C81D0[];
extern char D_00468CF0[];
extern void func_00324EB0(void *arg);
extern int CreateThread(struct ThreadParam *p);
extern int ChangeThreadPriority(int tid, int prio);
extern int func_003B0BA8(int tid, int a);
extern int func_00325360(int tid);

__attribute__((section(".text.func_003253C0")))
void func_003253C0(void)
{
    struct ThreadParam tp;

    tp.entry = func_00324EB0;
    tp.stack = D_003C81D0;
    tp.stackSize = 0x800;
    tp.initPriority = D_003CF9D8;
    tp.gpReg = D_00468CF0;
    D_003C8138 = CreateThread(&tp);
    (void)D_003C8138;
    func_003B0BA8(D_003C8138, 0);
    if (D_003C8138 != 0) {
        func_00325360(D_003C8138);
        (void)D_003C8138;
    }
    ChangeThreadPriority(D_003C8138, D_003C80B4);
}
