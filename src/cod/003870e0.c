extern int func_00387430(int a0);
extern void *func_00377998(void);

__attribute__((section(".text.func_003870E0")))
int func_003870E0(short id)
{
    int st;
    char *node;

    st = func_00387430(id);
    if (st & 8)
        return -1;
    node = func_00377998();
    if (node == 0)
        return -1;
    *(short *)(node + 0xC) = id;
    *(short *)(node + 0) = 1;
    node[8] = 0x10;
    node[9] = 2;
    *(short *)(node + 0xA) = 2;
    *(int *)(node + 4) = 0;
    return 0;
}
