/* sn-2.95.3-136 matched TU. */

extern void StateObj_runStep(unsigned char *p);
extern void func_003851C0(unsigned char *p);
extern void func_00385308(unsigned char *p, int b, int c);
extern void func_00385410(unsigned char *p);

__attribute__((section(".text.func_00384FA8")))
void func_00384FA8(unsigned char *p, int b) {
    switch (p[4]) {
    case 0:
        StateObj_runStep(p);
        break;
    case 1:
        func_003851C0(p);
        break;
    case 2:
    case 3:
        func_00385308(p, b, (unsigned char)(p[4] - 2));
        break;
    case 4:
        func_00385410(p);
        break;
    }
}
