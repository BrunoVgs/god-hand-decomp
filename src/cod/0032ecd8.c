/* cygnus-2.96 matched TU. */

extern void Obj33F8_Tramp_0033F130_FCB0(void *a0);
extern int ForwardField3ByOffset_32ED48(void *a0, int a1, int a2);
extern char D_00452FB0[];
extern char D_00452FD8[];

typedef struct {
    char pad[0x1E8];
    int unk1E8;
    int unk1EC[33];
} Obj;

/* Needs c_flags_drop -f=-freorder-blocks (like 0032dd18.c / 0032b7.c):
   with the global flag the obj == 0 block is moved to the end. */
__attribute__((section(".text.func_0032ECD8")))
void func_0032ECD8(Obj *obj, int idx, int val) {
    if (obj == 0) {
        Obj33F8_Tramp_0033F130_FCB0(D_00452FB0);
        return;
    }
    if (idx > 0x20) {
        Obj33F8_Tramp_0033F130_FCB0(D_00452FD8);
        return;
    }
    obj->unk1EC[idx] = val;
    ForwardField3ByOffset_32ED48(obj, idx, obj->unk1E8 + val);
}
