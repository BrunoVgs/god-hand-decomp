/* sn-2.95.3-136 matched 80-byte Phase A functions. */

extern void ClearField90_13E400(void *);
extern void ResetBlendFields_13C930(void *);
extern void ResetAnimSlotArray_13F510(void *);
extern void IdHolder_releaseAnim(void *);
extern void ClearActiveSlot_147188(void *);
extern void cCockPlBar_initData(void *);
extern char D_00420CA0[];
extern char D_00421BB8[];
extern char D_00422A80[];
extern char D_00427A58[];
extern void func_002AD288(void *, int);
extern void SetField214PtrThenInit_1B6F38(void *, void *);
extern void func_002B2400(void *);
extern void func_002BF708(void *);
extern void SysFlags_saveAndFreeze(void *);
extern int D_003C264C;
extern void func_002C0A08(int);
extern void func_002C09E8(int);
extern void func_003A52F0(void *, int, int);
extern void func_00378C48(void *);
extern void func_0037B0E0(void *);
extern void func_00379190(void *);
extern void func_00379BC0(void *);
extern short func_0037D760(void *);
extern void func_0037D728(void *);
extern void func_00380E10(void *);
extern void func_00381D38(void *, void *, void *);
extern void func_00383438(void *, void *);
extern void func_00380E88(void *, void *, void *);

__attribute__((section(".text.func_00378BF8")))
void func_00378BF8(char *self)
{
    func_00378C48(self);
    func_0037B0E0(self);
    if (self[6] == 0)
        func_00379190(self);
    else
        func_00379BC0(self);
}

__attribute__((section(".text.func_0037C2E0")))
void func_0037C2E0(char *dst, char *src)
{
    *(short *)(dst + 0x46) = func_0037D760(src + 0x20);
    *(unsigned short *)(dst + 0x48) = *(unsigned short *)(src + 0x3C);
    *(unsigned short *)(dst + 0x2E) = *(unsigned short *)(src + 0x1E);
    func_0037D728(dst);
}

__attribute__((section(".text.func_00380DC0")))
void func_00380DC0(char *self)
{
    func_00380E10(self);
    func_00381D38(self, self + 0x348, self + 0x318);
    func_00383438(self, self + 0x370);
    func_00380E88(self, self + 0x484, self + 0x470);
}
