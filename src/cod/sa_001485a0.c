/* sn-2.95.3-136: stage model state setup, returns the end of its packet data (0x1485A0). */
extern int func_00155138(char *p);
extern int func_00155248(char *p);
extern void func_00154A90(char *p, int buf, int c);
extern void func_00155358(char *p, int buf, int c);
extern void func_00148F50(char *u, char **mp, void *box);
extern void func_001490B0(char *u, char **mp, void *box);

__attribute__((section(".text.func_001485A0")))
int func_001485A0(char *state, char *a, int b, int flags, int n, void *box, int arg)
{
    char *hold[4];
    int big;
    unsigned short cnt;

    *(int *)(state + 0x400) = b;
    state[0x384] = 0;
    *(int *)(state + 0x380) = flags;
    *(int *)(state + 0x410) = 0;
    *(char **)(state + 0x388) = a;
    hold[0] = a;
    cnt = *(unsigned short *)(a + 8);
    state[0x386] = cnt;
    big = *(unsigned short *)(a + 8) >= 2;
    if (big) {
        int size = func_00155138(state);
        *(int *)(state + 0x408) = arg;
        func_00154A90(state, arg, 0);
        arg += size;
    } else {
        int size = func_00155248(state);
        *(int *)(state + 0x408) = arg;
        func_00155358(state, arg, 0);
        arg += size;
    }
    if (flags & 0x01000000) {
        func_00148F50(state, hold, box);
    } else {
        func_001490B0(state, hold, box);
    }
    return arg;
}
