/* sn-2.95.3-136 matched 84-byte Phase A functions. */

extern int func_0012B328(void *);
extern void cOmThrow_SetParent(void *, void *);
extern void cHeap_free(int, void *);
extern void __builtin_delete(void *);
extern void func_002A9800(void *, void *);
extern int cCoreSave_getGameLevel(void *);
extern char D_00569B70[];
extern float D_00428000[];
extern char D_004294F0[];
extern char D_007419A0[];
extern void espSys_effDataRelease(void *, int);
extern void SetField214PtrThenInit_1B6F38(void *, void *);
extern void Slot2_hideBankLayerIds(void *);
extern void displayScrollLayer(int, int);
extern void CustomIDWork_SetNumber(void *);
extern void SetCustomIDDispOneOrAll_1F29C0(void *, int, int);
extern char D_0044E538[];
extern char D_0044F1C8[];
extern void ReleaseObj(void *);
extern void func_002FBE28(void *, void *);
extern int GuardedCall_00329FD0_329F98(int);
extern void func_003298C0(int);
extern void func_0031C900(int);
extern int func_0032DC58(int);
extern void func_0032D6F0(int);
extern int cOmBase_checkDamage(void *, void *);

__attribute__((section(".text.func_00380D68")))
void func_00380D68(int unused, char *self)
{
    int value;
    if (*(int *)(self + 0x30) == 0)
        return;
    if (GuardedCall_00329FD0_329F98(*(int *)(self + 0x30)) != 5)
        return;
    func_003298C0(*(int *)(self + 0x30));
    value = *(int *)(self + 0x34);
    *(int *)(self + 0x30) = 0;
    func_0031C900(value);
}

__attribute__((section(".text.func_00381CE0")))
void func_00381CE0(int unused, char *self)
{
    int value;
    if (*(int *)(self + 0x20) == 0)
        return;
    if (func_0032DC58(*(int *)(self + 0x20)) != 5)
        return;
    func_0032D6F0(*(int *)(self + 0x20));
    value = *(int *)(self + 0x24);
    *(int *)(self + 0x20) = 0;
    func_0031C900(value);
}
