extern int GuardedCall_00329FD0_329F98(int);

__attribute__((section(".text.func_00374170")))
int func_00374170(int *p)
{
    if (*p == 0)
        return 0;
    return GuardedCall_00329FD0_329F98(*p);
}
