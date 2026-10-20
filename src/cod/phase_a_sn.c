/* sn-2.95.3-136 matched Phase A functions. */
#include "include_asm.h"

typedef struct {
    char pad[0x75];
    char f75;
    char f76;
} PhaseAObj;

typedef struct {
    PhaseAObj *obj;
    int a;
    int b;
} PhaseAEnt;

typedef struct {
    char pad[0x22F4];
    PhaseAEnt e[17];
} PhaseAOwner;

typedef struct {
    int a;
    int b;
} PhaseATask;

typedef struct {
    char pad[0x54];
    PhaseATask t[1];
} PhaseAScenario;

typedef union {
    float f;
    unsigned int u;
} PhaseAFloatBits;

typedef struct {
    long v0;
    char pad0[0x18];
    long v20;
    char pad1[0x18];
    long v40;
    char pad2[0x18];
    long v60;
    char pad3[0x18];
    long v80;
} PhaseAFloatState;

typedef struct {
    char pad[0x10];
    int f10;
    int f14;
} PhaseADeleteObject;

typedef struct {
    char pad[0xA6];
    unsigned short a6;
    unsigned short a8;
    char mid[4];
    unsigned short ae;
    unsigned short b0;
} PhaseAPanel;

typedef struct {
    int f0;
    unsigned char f4;
} PhaseARelEnt;

typedef struct {
    char raw[0x58];
} PhaseASlot58;

typedef struct {
    PhaseASlot58 *items;
} PhaseASlotParent;

typedef struct {
    char pad[0x84];
    int id;
} PhaseAInner84;

typedef struct {
    PhaseAInner84 *p;
} PhaseAOuter84;

typedef struct {
    int a;
    int b;
} PhaseAPair;

typedef struct {
    char bytes[16];
} PhaseAQuadword;

typedef struct {
    char pad[0x98];
    int f98;
    int f9C;
} PhaseAObj98;

typedef struct {
    char pad[0x20];
    short delta;
    short index;
    float (*function)(char *);
} PhaseAVtSlot;

typedef struct {
    char bytes[32];
} PhaseASlot32;

typedef struct {
    char pad[0x112];
    unsigned short messNo;
} PhaseAMessageScenario;

extern int D_00747A80;
extern char D_00569B70[];
extern char D_005E85F8;
extern char D_005FEE00[];
extern char D_005F38F0[];
extern void *D_003C2F84;
extern int IsTargetVisible_14B470(void *);
extern int cGameObj_isClip(void *);
extern int cIDBase_initialize(void *, int, int);
extern void cCoreSave_clearStateBit0(void *);
extern void SetGlobalToggle_375700(int);
extern void cOmBase_tickModeTableSkip381(void *);
extern void func_001B7EE0(void *, float);
extern void KillEffect(void *, int, int);
extern void cOmBase_dieCommon(void *);
extern void func_001DD068(void *);
extern void func_001DEC70(void *);
extern void func_001E8DF0(void *, void *, void *, unsigned short);
extern void func_002A58D8(void *, unsigned int);
extern int cSnd_SeIsLoaded(void *, int);
extern void UpdateObjWithVtableDispatch_2BB1F0(void *);
extern void cIDBase(void *);
extern int ForwardEntityAndExit_2C2368(void);
extern void cScenario_taskExec(void *, void *, void *, int);
extern void func_003A52F0(void *, int, int);
extern void cCoreSave_setSkill(void *, int, signed char);
extern void System_sendBootRequests(void *);
extern void func_002C9E78(void *);
extern void func_002C9F58(void *);
extern void UpdateObjByIndexedOp_2FBE50(void *, int, int);
extern void func_00302918(void *);
extern void Esp_killByGroup(int);
extern void func_00300C00(int, int);
extern void cHeap_free();
extern void func_0032B300(int, int);
extern void func_0032E040(int, int);
extern void *PathFinding(void *);
extern void func_002A9708(void *);
extern void __builtin_delete(void *);
extern void func_002B1C80(void *);
extern void func_002BE6C8(void *);
extern int ReqQueue_push(int, int, int, int, int);
extern void func_002D5788(void *, int);
extern int func_003244C8(int);
extern void func_002B1F80(
    void *, int, void *, float, float, float, float);
extern PhaseAQuadword D_0061B660;
extern void cDataSlot_resetSeHandles(void *);
extern char D_005E79D0[];
extern int func_002B5AF8(void *, int, void *);
extern void Forward325F20_3466A8(void *);
extern void *D_003C3CF0;
extern int EnsureInitThenForward_2A9538_30EE08(void *, int, void *);
extern int cIDBase_trans(void *);
extern int cIDBase_release(void *);
extern void cDamageUnit_SetDamageCollActive(void *, int);
extern PhaseAObj98 **D_003C2384;
extern int func_003B4220(void *, int);
extern char D_0042C0E0[];
extern int D_00568280;
extern void ActorRec_reset(void *);
extern char D_0044BED0[];
extern void func_002BB018(void *, int);
extern void func_002BB760(void *, void *, void *, float);
extern int GuardedCall_00329FD0_329F98(int);
extern int func_0032DCD0(int);
extern int func_0037FE78(void *, void *);
extern void func_002E0DE8(int, int, int, char *, ...);
extern char D_0045CD40[];
extern int *D_003FA62C;
extern char D_0045F5C0[];
extern int func_003AE188(int, int, ...);
extern void func_003A7B48(void) __attribute__((noreturn));
extern void IdPair_init(void *);
extern void cIDBase_restartAnim(void *);
extern void ClearFields_1614D0(void *);
extern void cIDBase_move(void *);
extern void CustomIDWork_SetMoveOffsetPosXSin(
    void *, int, unsigned short);
extern void CustomIDWork_ResetMoveOffsetPos(void *);
extern int SearchCameraData(int);
extern void func_002B4428(void *, int, int);
extern int func_002B4518(void *, int);
extern void func_002B4598(void *);
extern void func_002B45C8(void *);
extern void func_002B45F0(void *);
extern int func_002B8A30(void *, int);
extern int D_005E8040;
extern int func_00346848(void *);
extern char D_00754200[];
extern int D_00747B10;
extern int D_00747B14;
extern void func_0030F2B0(unsigned int);
extern int func_0037D1A8(int, int);
extern unsigned char D_0076A7B4;
extern PhaseASlot32 D_0076EA50[];
extern void ClearEventFlagsPending_375FA0(void);
extern void ClearPendingEntries_376008(void);
extern void func_00376370(void);
extern void func_0037BE98(void);
extern void ClearPendingFlagEvents_376E38(void);
extern void func_00376EA0(void);
extern void func_003774A8(void);
extern void func_00378AE0(void *);
extern void func_0037B0E0(void *);
extern void func_00378D18(void *);
extern void func_003794D0(void *);
extern void func_0037ACA0(void *);
extern void func_0037AEC0(void *);
extern void func_0037D680(void *);
extern int func_0037E8D8(void *);
extern char D_005CAC90[];
extern char D_005CAE50[];
extern void *func_002A5AD0(char *);
extern void func_0012E5C8(void *);
extern char D_005CB020[];
extern char D_005CB300[];
extern void cIDParam(void *);
extern void func_00309000(void *);
extern char D_00583F20[];
extern int GetField_110C_2019F8(char *);
extern void func_0031A808(void *);
extern int D_003C23A4;
extern int cMessage_ckMessage(int, int);
extern int cCoreSave_getSkill(void *, int);
extern void func_002E0B78(
    int, int, int, int, int, int, int, char *, void *);
extern void func_00381CE0(void *, void *);
extern void func_00380D68(void *, void *);
extern void func_00381DC0(void *, void *, void *);
extern void func_00380F10(void *, void *, void *);
extern void func_00381D38(void *, void *, void *);
extern void func_00380E88(void *, void *, void *);
extern char D_005FEE00[];
extern void cSnd_SeCall_2CBA48(
    void *, int, int, void *, int, int, int, int);
extern void func_001851C0(void *, int);
extern void moveMotion(void *);
extern int Obj0000_Get_Field_1560_Bit0_27DD00(int);
extern void displayScrollLayer(int, int);
extern float func_0031CF78(void);
extern void ForwardSoundEventAll_375DE0(short, short);
extern void BuildSoundEventEntry_375E78(int, short, short);
extern void StoreSoundEntry_3749D8(int, void *);
extern int func_00380F80(void *, void *, void *);
extern unsigned short D_0076C8C0;
extern int BuildSoundEvent_375BF0(void *);
extern char D_0045C3E0;

__attribute__((section(".text.func_00183510")))
void func_00183510(void *self)
{
    cSnd_SeCall_2CBA48(D_005FEE00, 2, 0xA, self, 0, 0, 0, 0);
}

__attribute__((section(".text.func_001BFCE8")))
void func_001BFCE8(void *self)
{
    cSnd_SeCall_2CBA48(D_005FEE00, 2, 0xA, self, 0, 0, 0, 0);
}

__attribute__((section(".text.func_00185180")))
void func_00185180(unsigned char *self)
{
    if (self[0x65B] != 0)
        return;
    func_001851C0(self, 4);
    self[0x65B] = 1;
}

__attribute__((section(".text.func_001CA1F8")))
void func_001CA1F8(unsigned char *self)
{
    switch (self[0x2F6]) {
    case 0:
        self[0x2F6]++;
    case 1:
        moveMotion(self);
        break;
    }
}

__attribute__((section(".text.func_0027E3F8")))
void func_0027E3F8(unsigned char *self)
{
    switch (self[0x2F6]) {
    case 0:
        self[0x2F6]++;
    case 1:
        moveMotion(self);
        break;
    }
}

__attribute__((section(".text.func_001FCCC0")))
void func_001FCCC0(char *self)
{
    if (*(short *)(self + 0x30) != 0) {
        *(short *)(self + 0x30) -= 1;
        if (*(short *)(self + 0x30) == 0) {
            unsigned int *flags = *(unsigned int **)(self + 0x28);
            *flags &= 0xFFFFFFFDU;
        }
    }
}

__attribute__((section(".text.cEm00_ckDown")))
int cEm00_ckDown(char *self)
{
    unsigned long value;
    int result;
    if ((*(unsigned short *)(self + 0x3AC) & 8) == 0)
        return 0;
    result = 1;
    value = *(unsigned long *)(self + 0x2F0);
    if ((value & 0xFFFF00000000UL) == 0x20200000000UL)
        result = 0;
    return result;
}

__attribute__((section(".text.func_00275D68")))
int func_00275D68(char *self)
{
    int child;
    if (*(int *)(self + 0x564) != 0x264)
        return 0;
    child = *(int *)(self + 0x740);
    if (child == 0)
        return 0;
    return Obj0000_Get_Field_1560_Bit0_27DD00(child) != 0;
}

__attribute__((section(".text.func_00298C18")))
void func_00298C18(int mode)
{
    if (mode == 3)
        displayScrollLayer(0x16, 0);
    else
        displayScrollLayer(0x16, 1);
}

__attribute__((section(".text.func_00373118")))
int func_00373118(char *object, int value, char *source, int enabled)
{
    int flags = *(int *)(object + 0x4C);
    *(int *)(object + 0x48) = 1;
    *(int *)(object + 0x74) = value;
    *(int *)(object + 0x7C) = *(int *)(source + 8);
    *(int *)(object + 0x6C) = *(int *)(source + 4);
    *(int *)(object + 0x4C) = flags | 1;
    if (enabled)
        *(int *)(object + 0x4C) |= 0x10;
    return 1;
}

__attribute__((section(".text.func_0037A668")))
void func_0037A668(char *object)
{
    char *entry = object + 0x12C;
    if (entry[7] < 0x29)
        *(int *)(object + 0xC) = BuildSoundEvent_375BF0(entry);
}

__attribute__((section(".text.func_00380638")))
void func_00380638(char *object)
{
    int difference = *(int *)(object + 0xC) - *(int *)(object + 8);
    func_002E0DE8(3, (short)(difference + 7), 0xC, &D_0045C3E0);
}

__attribute__((section(".text.func_0031CF30")))
float func_0031CF30(void)
{
    float result = func_0031CF78();
    if (result <= 0.0f)
        result = result + 1.0f;
    return result;
}

__attribute__((section(".text.func_00375D98")))
void func_00375D98(int target, short a, short b)
{
    if (target == 0)
        ForwardSoundEventAll_375DE0(a, b);
    else
        BuildSoundEventEntry_375E78(target, a, b);
}

__attribute__((section(".text.func_0037B720")))
void func_0037B720(signed char *self)
{
    int index;
    if (self[0x29] == 0)
        return;
    index = self[0x27];
    StoreSoundEntry_3749D8(
        index, (char *)self + 0x16C + (index << 5));
    self[0x29] = 0;
}

__attribute__((section(".text.func_003833B0")))
void func_003833B0(void *a0, unsigned char *a1)
{
    int result;
    if (((a1[3] ^ 1) & 1) != 0) {
        result = func_00380F80(a0, a1 + 0x34, a1);
        if (result)
            a1[1] = (unsigned char)result;
    }
}

__attribute__((section(".text.func_0037CA98")))
void func_0037CA98(void)
{
    unsigned short *entry = &D_0076C8C0;
    unsigned int sentinel = 0xFFFFFFFFU;
    int count;
    unsigned int value;
    count = 0x32;
    do {
        if (*entry != 0) {
            value = *(unsigned int *)((char *)entry + 0xC);
            if (value != sentinel)
                *(unsigned int *)((char *)entry + 0xC) = value + 1;
        }
        entry = (unsigned short *)((char *)entry + 0x20);
        count -= 1;
    } while (count >= 0);
}

__attribute__((section(".text.func_002A72C8")))
void func_002A72C8(int init, int priority)
{
    if (priority == 0xFFFF && init) {
        func_002A5AD0(D_005CAC90);
        func_0012E5C8(D_005CAE50);
    }
}

__attribute__((section(".text.func_002ACBE8")))
void func_002ACBE8(int init, int priority)
{
    if (priority == 0xFFFF && init) {
        cIDParam(D_005CB020);
        func_00309000(D_005CB300);
    }
}

__attribute__((section(".text.func_002BE200")))
void func_002BE200(void *self)
{
    if (GetField_110C_2019F8(D_00583F20) == 0)
        func_0031A808(self);
}

__attribute__((section(".text.cScenario_isMessOn")))
int cScenario_isMessOn(PhaseAMessageScenario *self)
{
    if (self->messNo == 0xFFFF)
        return 0;
    return cMessage_ckMessage(D_003C23A4, self->messNo);
}

__attribute__((section(".text.func_002C9A90")))
int func_002C9A90(int *self, int index)
{
    if (*self == 0)
        return 0;
    return cCoreSave_getSkill(
        D_00569B70, *((signed char *)self + index + 0x14));
}

__attribute__((section(".text.func_002C9BB0")))
void func_002C9BB0(int *self, int index, unsigned char value)
{
    if (*self)
        cCoreSave_setSkill(
            D_00569B70, *((signed char *)self + index + 0x14), value);
}

__attribute__((section(".text.func_002E0D60")))
void func_002E0D60(
    int a, int b, int c, int d, int e, int f, char *format, ...)
{
    func_002E0B78(
        a, b, c, d, e, f, 0, format,
        (char *)__builtin_next_arg(format) - 8);
}

__attribute__((section(".text.func_00378070")))
void func_00378070(short *values)
{
    int result = values[0] + values[2];
    if (values[2] > 0)
        result = values[1] < result ? values[1] : result;
    else
        result = result < values[1] ? values[1] : result;
    values[0] = result;
    ((unsigned short *)values)[3]++;
}

__attribute__((section(".text.func_00382F00")))
void func_00382F00(void *a0, unsigned char *a1)
{
    if (a1[3] & 1)
        func_00381CE0(a0, a1 + 0xA4);
    else
        func_00380D68(a0, a1 + 0x34);
}

__attribute__((section(".text.func_003833F8")))
void func_003833F8(void *a0, unsigned char *a1)
{
    if (a1[3] & 1)
        func_00381DC0(a0, a1 + 0xA4, a1);
    else
        func_00380F10(a0, a1 + 0x34, a1);
}

__attribute__((section(".text.func_00383438")))
void func_00383438(void *a0, unsigned char *a1)
{
    if (a1[3] & 1)
        func_00381D38(a0, a1 + 0xA4, a1);
    else
        func_00380E88(a0, a1 + 0x34, a1);
}

__attribute__((section(".text.func_00375180")))
int func_00375180(void)
{
    if (func_0037D1A8(1, 0))
        return 1;
    return D_0076A7B4 != 0;
}

__attribute__((section(".text.func_00375A78")))
void func_00375A78(short index)
{
    func_003A52F0(&D_0076EA50[index], 0, 32);
}

__attribute__((section(".text.func_00375F68")))
void func_00375F68(void)
{
    ClearEventFlagsPending_375FA0();
    ClearPendingEntries_376008();
    func_00376370();
    func_0037BE98();
}

__attribute__((section(".text.func_00376E00")))
void func_00376E00(void)
{
    ClearPendingFlagEvents_376E38();
    func_00376EA0();
    func_003774A8();
    func_0037BE98();
}

__attribute__((section(".text.func_00378AA8")))
void func_00378AA8(void *self)
{
    func_00378AE0(self);
    func_0037B0E0(self);
    func_00378D18(self);
}

__attribute__((section(".text.func_00378CE0")))
void func_00378CE0(void *self)
{
    func_00378AE0(self);
    func_0037B0E0(self);
    func_003794D0(self);
}

__attribute__((section(".text.func_0037AC68")))
void func_0037AC68(void *self)
{
    func_0037ACA0(self);
    func_0037B0E0(self);
    func_0037AEC0(self);
}

__attribute__((section(".text.func_0037C2A8")))
void func_0037C2A8(unsigned char *destination, unsigned char *source)
{
    *(unsigned short *)(destination + 0x40) =
        *(unsigned short *)(source + 0x34);
    *(unsigned short *)(destination + 0x42) =
        *(unsigned short *)(source + 0x36);
    *(unsigned short *)(destination + 0x2C) =
        *(unsigned short *)(source + 0x1C);
    func_0037D680(destination);
}

__attribute__((section(".text.func_0037E488")))
void func_0037E488(unsigned char *self)
{
    if (func_0037E8D8(self))
        self[2] = 0xC;
    else
        self[2] = 1;
}

__attribute__((section(".text.func_0037FE40")))
void func_0037FE40(unsigned char *self)
{
    if (func_0037FE78(self, self + 0x370))
        self[2] = 1;
}

__attribute__((section(".text.func_00146878")))
void func_00146878(char *self)
{
    IdPair_init(self);
    *(short *)(self + 0x100) = 0;
    cIDBase_restartAnim(self);
    self[0x1C] = 1;
}

__attribute__((section(".text.func_00164EF8")))
void func_00164EF8(char *self)
{
    ClearFields_1614D0(self);
    *(int *)(self + 0x298) = 0;
    self[0x5A] = 0;
    self[0x5B] = 0;
    self[0x5C] = 0;
    self[0x5D] = 0;
}

__attribute__((section(".text.func_001661A0")))
void func_001661A0(char *self)
{
    cIDBase_move(self + 0x100);
    cIDBase_move(self + 0x180);
    cIDBase_move(self + 0x230);
}

__attribute__((section(".text.func_00167F70")))
void func_00167F70(char *self)
{
    ClearFields_1614D0(self);
    self[0x5A] = 0;
    self[0x5B] = 0;
    self[0x5C] = 0;
    self[0x5D] = 0;
    self[0x90] = 0;
}

__attribute__((section(".text.func_001DE050")))
void func_001DE050(char *self, int enabled)
{
    if (enabled)
        CustomIDWork_SetMoveOffsetPosXSin(self + 0x162C, 4, 8);
    else
        CustomIDWork_ResetMoveOffsetPos(self + 0x162C);
}

__attribute__((section(".text.func_001DF820")))
void func_001DF820(char *self, int enabled)
{
    if (enabled)
        CustomIDWork_SetMoveOffsetPosXSin(self + 0x440, 4, 8);
    else
        CustomIDWork_ResetMoveOffsetPos(self + 0x440);
}

__attribute__((section(".text.func_001ED4B0")))
void func_001ED4B0(char *self, int enabled)
{
    if (enabled)
        CustomIDWork_SetMoveOffsetPosXSin(self + 0x11D0, 3, 0x10);
    else
        CustomIDWork_ResetMoveOffsetPos(self + 0x11D0);
}

__attribute__((section(".text.func_001EE730")))
void func_001EE730(char *self, int enabled)
{
    if (enabled)
        CustomIDWork_SetMoveOffsetPosXSin(self + 0xDF0, 3, 0x10);
    else
        CustomIDWork_ResetMoveOffsetPos(self + 0xDF0);
}

INCLUDE_ASM("nonmatching", func_002998A0);

__attribute__((section(".text.func_002B3158")))
void func_002B3158(char *self)
{
    *(int *)(self + 0x10) = 0;
    *(int *)(self + 0x14) |= 8;
    *(int *)(self + 0x98) = 0;
    *(int *)(self + 0x9C) = 0;
    *(int *)(self + 0xA0) = 0;
    func_002B45C8(self);
}

__attribute__((section(".text.func_002B41F0")))
void func_002B41F0(char *self)
{
    func_002B45F0(self);
    *(int *)(self + 0x14) &= ~0x10;
    *(int *)(self + 0x10) = 0;
}

__attribute__((section(".text.func_002B4528")))
void func_002B4528(void *self, int camera)
{
    func_002B4428(self, 1, SearchCameraData(camera));
}

__attribute__((section(".text.func_002B4560")))
void func_002B4560(void *self)
{
    if (func_002B4518(self, 1))
        func_002B4598(self);
}

__attribute__((section(".text.func_002B8A70")))
void func_002B8A70(char *self, int value)
{
    *(int *)(self + 0x10) = value;
    self[0xC] = (char)func_002B8A30(&D_005E8040, value);
}

__attribute__((section(".text.func_002BA6B0")))
void func_002BA6B0(char *self)
{
    PhaseAVtSlot *object = *(PhaseAVtSlot **)(self + 0x100);
    *(float *)(self + 0xE4) =
        object->function(self + object->delta);
}

__attribute__((section(".text.func_002D4210")))
int func_002D4210(char *self)
{
    void *object = *(void **)self;
    int result = 0;
    if (object != 0) {
        result = func_00346848(object);
        *(int *)(self + 0xA4) = result;
    }
    return result;
}

__attribute__((section(".text.func_002D5790")))
void func_002D5790(char *self)
{
    *(void **)(self + 0x10) = (void *)EnsureInitThenForward_2A9538_30EE08(
        (void *)*(int *)(self + 8), 0x10, D_00754200);
}

__attribute__((section(".text.func_00306ED8")))
int func_00306ED8(char *self, int index)
{
    char *entry;
    int value;
    if (index < 0x20) {
        entry = *(char **)(self + (index << 2) + 0x300);
        if (entry != 0)
            goto found;
    }
    return -1;
found:
    value = *(unsigned short *)(entry + 0xA) + 1;
    *(unsigned short *)(entry + 0xA) = value;
    return (short)value;
}

__attribute__((section(".text.func_0031CEB8")))
void func_0031CEB8(void)
{
    D_00747B10 = 0x3124;
    D_00747B14 = 0x66B;
    func_0030F2B0(0xD8A9523D);
}

__attribute__((section(".text.func_0018A3B8")))
void func_0018A3B8(char *self, int index)
{
    void *unit;
    self += index << 2;
    unit = *(void **)(self + 0x600);
    if (unit != 0)
        cDamageUnit_SetDamageCollActive(unit, 0);
}

INCLUDE_ASM("nonmatching", func_001D4980);

INCLUDE_ASM("nonmatching", func_001D49B0);

__attribute__((section(".text.func_001D4F48")))
void func_001D4F48(char *self)
{
    PhaseAObj98 *object;
    cIDBase_release(self + 0x10);
    object = *D_003C2384;
    object->f9C = 0;
    object->f98 = 0;
}

__attribute__((section(".text.func_001E7440")))
void func_001E7440(char *self)
{
    cIDBase_trans(self + 0x530);
    cIDBase_trans(self);
}

__attribute__((section(".text.func_001F28C0")))
void func_001F28C0(char *self)
{
    cIDBase_release(self + 0x930);
    cIDBase_release(self + 0x10);
}

__attribute__((section(".text.func_001F2990")))
void func_001F2990(char *self)
{
    cIDBase_trans(self + 0x10);
    cIDBase_trans(self + 0x930);
}

__attribute__((section(".text.func_001F6E68")))
int func_001F6E68(void)
{
    D_00568280 = func_003B4220(D_0042C0E0, 2);
    return 1;
}

__attribute__((section(".text.func_001FCDB8")))
void func_001FCDB8(char *self)
{
    ActorRec_reset(self);
    *(int *)(self + 0x34) = 0;
    self[0x49] = 1;
}

__attribute__((section(".text.func_002BAFE0")))
void func_002BAFE0(char *self, int flags)
{
    *(char **)(self + 0x100) = D_0044BED0;
    if (flags & 1)
        func_002BB018(self, 0x110);
}

__attribute__((section(".text.func_002BD7F8")))
void func_002BD7F8(void *a0, void *a1, void *a2)
{
    func_002BB760(a2, a0, a1, 0.0f);
}

__attribute__((section(".text.func_00374170")))
int func_00374170(int *p)
{
    if (*p == 0)
        return 0;
    return GuardedCall_00329FD0_329F98(*p);
}

__attribute__((section(".text.func_00374928")))
int func_00374928(int *p)
{
    if (*p == 0)
        return 0;
    return func_0032DCD0(*p);
}

__attribute__((section(".text.func_00383848")))
void func_00383848(char *self)
{
    if (func_0037FE78(self, self + 0x370) != 0)
        self[2] = 0;
}

__attribute__((section(".text.func_00384B98")))
void func_00384B98(int unused, int value)
{
    func_002E0DE8(3, 0x18, 8, D_0045CD40, value);
}

__attribute__((section(".text.func_003A7B58")))
void func_003A7B58(int a0, int a1, int a2)
{
    func_003AE188(
        *(int *)((char *)D_003FA62C + 0xC), (int)D_0045F5C0, a2, a0, a1);
    func_003A7B48();
}

__attribute__((section(".text.func_002018D0")))
int func_002018D0(PhaseAOuter84 *outer)
{
    return func_003244C8(outer->p->id);
}

__attribute__((section(".text.func_002B2058")))
void func_002B2058(
    void *a0, int a1, void *a2, float f12, float f13, float f14, float f15)
{
    func_002B1F80(a0, a1, a2, f12, f13, f12 + f14, f13 + f15);
}

__attribute__((section(".text.func_002F1AA0")))
void func_002F1AA0(int enabled, unsigned int type)
{
    if (type == 0xFFFF && enabled != 0) {
        __asm__ __volatile__(
            "sqc2 $vf0, %0" : : "m"(D_0061B660) : "memory");
    }
}

__attribute__((section(".text.func_001FF448")))
void func_001FF448(PhaseAPair *object)
{
    if (object->b >= 0)
        cDataSlot_resetSeHandles(object);
}

__attribute__((section(".text.func_002B48A0")))
int func_002B48A0(int a0, void *a1)
{
    return func_002B5AF8(D_005E79D0, a0, a1);
}

__attribute__((section(".text.func_002B4BC0")))
void func_002B4BC0(unsigned char *object)
{
    if (object[0x14] != 0)
        Forward325F20_3466A8(object);
}

__attribute__((section(".text.func_002BADF8")))
int func_002BADF8(void *unused, void *p)
{
    return EnsureInitThenForward_2A9538_30EE08(p, 0x10, D_003C3CF0);
}

__attribute__((section(".text.func_002BE4E8")))
void func_002BE4E8(char *object)
{
    void *block = *(void **)(object + 0x4C0);
    if (block != 0)
        cHeap_free(*(int *)((char *)block - 0x20), block);
}

INCLUDE_ASM("nonmatching", func_002D4DA0);

__attribute__((section(".text.func_00306140")))
void func_00306140(void)
{
    Esp_killByGroup(0x20);
    func_00300C00(0x20, 1);
}

__attribute__((section(".text.func_0031C928")))
void func_0031C928(void *block, void *heap)
{
    if (block != 0)
        cHeap_free(heap, block);
}

__attribute__((section(".text.func_00373FA0")))
void func_00373FA0(int *p)
{
    if (*p)
        func_0032B300(*p, 1);
}

__attribute__((section(".text.func_00374570")))
void func_00374570(int *p)
{
    if (*p)
        func_0032E040(*p, 1);
}

__attribute__((section(".text.func_0015EEE0")))
void func_0015EEE0(PhaseAFloatState *p)
{
    PhaseAFloatBits bits;
    bits.f = 1.0f;
    p->v20 = 0;
    p->v80 = 0;
    p->v60 = 0;
    p->v40 = 0;
    p->v0 = (long)bits.u << 32;
}

__attribute__((section(".text.func_002A5AD0")))
void *func_002A5AD0(char *p)
{
    PathFinding(p + 0x18C);
    return p;
}

__attribute__((section(".text.func_002A96D8")))
void func_002A96D8(int *p, int a, int b, int c, int d)
{
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    func_002A9708(p);
}

__attribute__((section(".text.func_002AD288")))
void func_002AD288(PhaseADeleteObject *object, int flags)
{
    object->f14 = 0;
    object->f10 = 0;
    if (flags & 1)
        __builtin_delete(object);
}

__attribute__((section(".text.func_002B17F8")))
void func_002B17F8(PhaseAPanel *panel)
{
    panel->ae = panel->a6;
    panel->b0 = panel->a8;
    func_002B1C80(panel);
}

__attribute__((section(".text.func_002BE670")))
void func_002BE670(PhaseARelEnt *entry)
{
    func_002BE6C8(entry);
    entry->f4 = 0;
    entry->f0 = 0;
}

__attribute__((section(".text.func_002D30E0")))
int func_002D30E0(int a, int b, int c, int d)
{
    return ReqQueue_push(a, 1, b, c, d);
}

__attribute__((section(".text.func_002D51C0")))
void func_002D51C0(PhaseASlotParent *parent, int index, int value)
{
    func_002D5788(&parent->items[index], value);
}

__attribute__((section(".text.func_001020F0")))
int func_001020F0(void *p)
{
    if (D_00747A80 < 0)
        return 1;
    return IsTargetVisible_14B470(p) != 0;
}

__attribute__((section(".text.func_00107F20")))
int func_00107F20(void *p)
{
    if (D_00747A80 < 0)
        return 1;
    return cGameObj_isClip(p) != 0;
}

__attribute__((section(".text.func_0013ECF0")))
int func_0013ECF0(char *p)
{
    int result = cIDBase_initialize(p, 1, 2);
    *(short *)(p + 0xBE) = -1;
    return result;
}

__attribute__((section(".text.func_001415E8")))
void func_001415E8(PhaseAOwner *p, int value)
{
    int i;
    for (i = 0; i < 17; i++) {
        PhaseAObj *obj = p->e[i].obj;
        if (obj != 0) {
            obj->f75 = 1;
            obj->f76 = value;
        }
    }
}

__attribute__((section(".text.func_001672F0")))
void func_001672F0(void)
{
    cCoreSave_clearStateBit0(D_00569B70);
    SetGlobalToggle_375700(1);
    D_005E85F8 = 1;
}

__attribute__((section(".text.func_00167EB0")))
void func_00167EB0(void)
{
    cCoreSave_clearStateBit0(D_00569B70);
    SetGlobalToggle_375700(1);
    D_005E85F8 = 1;
}

__attribute__((section(".text.func_001A3FD8")))
void func_001A3FD8(void *p)
{
    cOmBase_tickModeTableSkip381(p);
    func_001B7EE0(p, 2.0f);
}

__attribute__((section(".text.func_001B8448")))
void func_001B8448(void *p)
{
    KillEffect(p, 0, 2);
    cOmBase_dieCommon(p);
}

__attribute__((section(".text.func_001DF858")))
void *func_001DF858(char *p)
{
    func_001DD068(p);
    func_001DEC70(p + 0x25B0);
    *(int *)(p + 0x2E50) = 0;
    return p;
}

__attribute__((section(".text.func_001E7E68")))
void func_001E7E68(void *a, void *b, void *c, unsigned short d)
{
    if (b != 0 && c != 0 && d < 0x16)
        func_001E8DF0(a, b, c, d);
}

__attribute__((section(".text.func_0026F2B8")))
int func_0026F2B8(unsigned char *p)
{
    unsigned char mode = p[0x2F4];
    if (mode == 1)
        return 1;
    if (mode == 2 && p[0x2F5] != mode)
        return 1;
    return 0;
}

__attribute__((section(".text.func_002A58A0")))
void func_002A58A0(char *p, int value)
{
    *(int *)(p + 0x2A060) = value;
    func_002A58D8(p, 0xFFFFFFFF);
}

__attribute__((section(".text.func_002B12A0")))
int func_002B12A0(unsigned short *p)
{
    switch (*p) {
    case 0: return 1;
    case 1: return 1;
    case 2: return 1;
    case 3: return 1;
    case 4: return 1;
    case 5: return 1;
    case 6: return 1;
    case 7: return 1;
    case 8: return 1;
    case 9: return 1;
    case 10: return 1;
    case 11: return 1;
    case 12: return 1;
    case 13: return 1;
    default:
        return 0;
    }
}

__attribute__((section(".text.func_002B31F8")))
int func_002B31F8(int *p)
{
    if (p[7] != 0)
        return cSnd_SeIsLoaded(D_005FEE00, p[8]);
    return 1;
}

__attribute__((section(".text.func_002B8AA8")))
void func_002B8AA8(int *p)
{
    int active;
    p[0x36] = 0;
    active = (p[0] & 0x203) == 3;
    if (active)
        UpdateObjWithVtableDispatch_2BB1F0((void *)p[0xD]);
}

static inline void phase_a_ctor(char *field)
{
    cIDBase(field + 0x20);
}

__attribute__((section(".text.func_002BF820")))
void func_002BF820(int init, int priority)
{
    if (priority == 0xFFFF && init)
        phase_a_ctor(D_005F38F0);
}

__attribute__((section(".text.func_002C2330")))
int func_002C2330(void *p)
{
    cScenario_taskExec(
        D_003C2F84, (void *)ForwardEntityAndExit_2C2368, p, 1);
    return 1;
}

__attribute__((section(".text.cScenario_clearTaskData")))
void cScenario_clearTaskData(PhaseAScenario *scenario, int index)
{
    if (index >= 0)
        func_003A52F0(&scenario->t[index], 0, 8);
}

__attribute__((section(".text.func_002C9B78")))
void func_002C9B78(int *p, int a, unsigned char b)
{
    if (*p)
        cCoreSave_setSkill(D_00569B70, a, b);
}

__attribute__((section(".text.func_002C9BF8")))
void func_002C9BF8(int *p, int index)
{
    if (*p)
        cCoreSave_setSkill(
            D_00569B70, *((signed char *)p + index + 0x14), -1);
}

__attribute__((section(".text.func_002C9D20")))
void func_002C9D20(void *p)
{
    System_sendBootRequests(p);
    func_002C9E78(p);
    func_002C9F58(p);
}

__attribute__((section(".text.func_002FEB80")))
void func_002FEB80(int *p, int a, int b)
{
    if (a == p[0x42] && b == p[0x43])
        UpdateObjByIndexedOp_2FBE50(p, a, b);
}

__attribute__((section(".text.func_003039E8")))
void func_003039E8(int *p, int a, int b)
{
    if (p[0x43] == a && p[0x44] == b)
        func_00302918(p);
}
