/* cygnus-2.96: func_0032D1A0, reference-counted init of the mwply handle table: the first caller clears
 * the table and installs the two server callbacks. */
extern void func_00324950(void);
extern int func_0032F230(void);
extern void *func_003A52F0(void *d, int c, unsigned int n);
extern int func_0033BA10(int a0, int a1, int a2, int a3, int t0);
extern int func_0033B810(int a0, int a1, int a2, int a3);
extern void func_0032D170(void);
extern void func_0032D198(void);
extern volatile int D_003D1470;
extern int D_003D1474;
extern int D_003D1478;
extern char D_003D1488[];
extern char D_00452980[];
extern char D_00452990[];

__attribute__((section(".text.func_0032D1A0")))
void func_0032D1A0(void)
{
    (void)D_003D1470;
    if (D_003D1474 == 0) {
        func_00324950();
        func_0032F230();
        func_003A52F0(D_003D1488, 0, 0x9E0);
        func_0033BA10(2, 0, (int)func_0032D170, 0, (int)D_00452980);
        D_003D1478 = func_0033B810(5, (int)func_0032D198, 0, (int)D_00452990);
    }
    D_003D1474++;
}
