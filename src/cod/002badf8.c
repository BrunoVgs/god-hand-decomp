extern char D_005FEE00[];
extern void *D_003C3CF0;
extern int EnsureInitThenForward_2A9538_30EE08(void *, int, void *);

__attribute__((section(".text.func_002BADF8")))
int func_002BADF8(void *unused, void *p)
{
    return EnsureInitThenForward_2A9538_30EE08(p, 0x10, D_003C3CF0);
}
