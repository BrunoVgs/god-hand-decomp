/* Cygnus helper requiring the compiler's original block order. */

extern long long D_00766C80;
extern void func_0035BA58(void);
extern int D_003D8480;
extern char D_00454098[];
extern void func_003B1F28(void *);
extern int func_003B9DE0(void *);
extern char D_00460928[];
extern int D_003EE084;
extern void MWSPR_SaveSprMem(void);
extern void func_003464D8(void);
extern void MWSPR_RestoreSprMem(void);
extern void func_003465B8(void);
extern void func_00348E18(void *);
extern void func_00348F68(void *);
extern char D_00460B20[];
extern int D_003D04B0;
extern char D_003D04D0[];
extern void func_003A52F0(void *, int, int);
extern int Obj33F8_Tramp_0033B658_FC70(void);
extern int Obj33F8_Tramp_0033B670_FC88(void);
extern int D_003D1E68;
extern char D_003D1E70[];
extern char D_00460AD0[];
extern char D_00460AF8[];

__attribute__((section(".text.func_00346498")))
int func_00346498(int a0, int a1, void *a2)
{
    if (D_003EE084 == 0)
        MWSPR_SaveSprMem();
    else
        func_003464D8();
}

__attribute__((section(".text.func_00346578")))
int func_00346578(void *a0, int a1, int a2)
{
    if (D_003EE084 == 0)
        MWSPR_RestoreSprMem();
    else
        func_003465B8();
}

__attribute__((section(".text.func_00331C98")))
void func_00331C98(int value)
{
    D_003D8480 = value;
    if (value == 1)
        func_003B1F28(D_00454098);
}

__attribute__((section(".text.func_00328190")))
void func_00328190(char *self)
{
    int state = *(int *)(self + 0x14);
    *(int *)(self + 0x34) = 0;
    *(int *)(self + 0x4C) = 0;
    if (state == 0)
        *(volatile char *)(self + 1) = 3;
    else
        *(volatile char *)(self + 1) = 2;
    self[2] = 0;
    *(int *)(self + 0x24) = 0;
    *(int *)(self + 0x28) = 0;
    self[0x47] = 1;
}

__attribute__((section(".text.func_003BA088")))
void func_003BA088(char *self)
{
    if (self == 0) {
        func_003B9DE0(D_00460928);
        return;
    }
    *(int *)(self + 0x24) = 1;
}

__attribute__((section(".text.func_0035BB08")))
long long func_0035BB08(void)
{
    if (D_00766C80 == 0)
        func_0035BA58();
    return D_00766C80;
}

__attribute__((section(".text.func_00348DD8")))
void func_00348DD8(char *object)
{
    int *state = (int *)(object + 0x2A4);
    if (*(int *)(object + 0x284) == 1 || *state == 1)
        func_00348E18(object);
    else
        func_00348F68(object);
}

__attribute__((section(".text.func_003BA8C0")))
void func_003BA8C0(char *object, void *a, void *b)
{
    if (object == 0)
        goto error;
    if (a == 0)
        goto error;
    if (b != 0)
        goto valid;
error:
    func_003B9DE0(D_00460B20);
    return;
valid:
    ((volatile int *)(object + 0x10))[1] = (int)b;
    ((volatile int *)(object + 0x10))[0] = (int)a;
}

__attribute__((section(".text.func_003279B8")))
int func_003279B8(void)
{
    int count;
    count = D_003D04B0 + 1;
    D_003D04B0 = count;
    if (count == 1)
        func_003A52F0(D_003D04D0, 0, 0xF00);
    return 1;
}

__attribute__((section(".text.func_003BA830")))
void func_003BA830(char *self, int *out_a, int *out_b)
{
    if (self == 0) {
        func_003B9DE0(D_00460AD0);
        return;
    }
    if (out_a != 0)
        *out_a = *(int *)(self + 0x1C);
    if (out_b != 0)
        *out_b = *(int *)(self + 0x20);
}

__attribute__((section(".text.func_003BA878")))
void func_003BA878(char *self, int *out_a, int *out_b)
{
    if (self == 0) {
        func_003B9DE0(D_00460AF8);
        return;
    }
    if (out_a != 0)
        *out_a = *(int *)(self + 0x10);
    if (out_b != 0)
        *out_b = *(int *)(self + 0x14);
}

__attribute__((section(".text.func_0032F288")))
int func_0032F288(void)
{
    Obj33F8_Tramp_0033B658_FC70();
    if (--D_003D1E68 == 0)
        func_003A52F0(D_003D1E70, 0, 0x6590);
    return Obj33F8_Tramp_0033B670_FC88();
}
