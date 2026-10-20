extern char D_005FEE00[];
extern void *PathFinding(void *);
extern void *func_002A5AD0(char *);

__attribute__((section(".text.func_002A5AD0")))
void *func_002A5AD0(char *p)
{
    PathFinding(p + 0x18C);
    return p;
}
