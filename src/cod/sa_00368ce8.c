/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
extern unsigned char D_0045A370;
extern char D_0045A320[];
extern char *volatile D_00766CD4[];
extern int func_00368D60(int n, void *buf);
extern void func_00366D18(void);
extern void func_00368AA0(void);

__attribute__((section(".text.func_00368CE8")))
int func_00368CE8(int n, void *buf)
{
    int r;
    unsigned char st = D_0045A370;

    D_00766CD4[0] = D_0045A320;
    if (st != 4) {
        for (;;)
            ((void (*)(void))-1)();
    }
    r = func_00368D60(n, buf);
    if (r != 0)
        return r;
    func_00366D18();
    func_00368AA0();
    return 0;
}
