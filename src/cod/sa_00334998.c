/* cygnus-2.96: func_00334998, stop a running stream: cancel its request, then poll until it leaves
 * state 2 (giving up with an error after 0x63FFF6 polls) and reset it. */
typedef struct Stream334998 {
    char unk00[2];
    char state;                 /* 0x02 */
    char unk03[0x25];
    int pos;                    /* 0x28 */
    void *req;                  /* 0x2C */
} Stream334998;

extern void func_00334008(Stream334998 *s, char *msg);
extern void func_00331570(void *req);
extern void func_00331AD8(void);
extern void func_003341B8(void);
extern int func_00334A90(Stream334998 *s);
extern void func_00333FD8(void);
extern void func_003260C8(char *msg);
extern char D_004549C0[];
extern char D_004549D8[];

__attribute__((section(".text.func_00334998")))
void func_00334998(Stream334998 *s)
{
    int n = 0;

    if (s == 0) {
        func_00334008(s, D_004549C0);
        return;
    }
    if ((unsigned char)s->state < 2)
        return;
    if (s->req != 0)
        func_00331570(s->req);
    for (;;) {
        func_00331AD8();
        func_003341B8();
        func_00334A90(s);
        if (s->state != 2)
            break;
        if (++n > 0x63FFF6) {
            func_003260C8(D_004549D8);
            break;
        }
        func_00333FD8();
    }
    s->state = 0;
    s->pos = 0;
}
