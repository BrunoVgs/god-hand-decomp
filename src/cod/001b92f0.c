/* sn-2.95.3-136 matched TU. */

extern int ClearField5B4IfFlagUnset_1B76B0(int a0);
extern void func_001B76D8(void *a0);
extern float cEmManage_GetSpeedRate(void *a0);
extern char D_005864F0[];
extern void cDamageUnit_SetDamageCollActive(int unit, int on);

#define PHASE_OBJ_STATE   0x2F4         /* state byte: index into the phase table */
#define PHASE_OBJ_RATE    0x5A8         /* speed rate float */

/* One phase entry: this-adjust, method index (or negative: inline handler), table offset in the object. */
typedef struct PhaseEnt {
    short adjust;                       /* 0x00 */
    short index;                        /* 0x02 */
    short tableOff;                     /* 0x04 */
    short unk06;
} PhaseEnt;
typedef struct PhaseTable { PhaseEnt e[1]; } PhaseTable;

extern PhaseTable D_003BDDA8;

#define PHASE_OBJ_COLL_A  0x600         /* damage collision units, switched off every tick */
#define PHASE_OBJ_COLL_B  0x608

/* Phase tick: switch off the object's two damage collision units, store the global speed rate in the object, run the handler the state byte's table entry names (from a method table found through the object, or inline), then the shared post-update steps. */
__attribute__((section(".text.func_001B92F0")))
void func_001B92F0(void *a0)
{
    char *s0 = (char *)a0;
    char *e;
    int i8;
    int f0;
    float rate;
    int type; int arg; int (*fp)(int); long entry;
    if (ClearField5B4IfFlagUnset_1B76B0((int)s0) == 0) return;
    if (*(int *)(s0 + PHASE_OBJ_COLL_A) != 0) {
        cDamageUnit_SetDamageCollActive(*(int *)(s0 + PHASE_OBJ_COLL_A), 0);
    }
    if (*(int *)(s0 + PHASE_OBJ_COLL_B) != 0) {
        cDamageUnit_SetDamageCollActive(*(int *)(s0 + PHASE_OBJ_COLL_B), 0);
    }
    rate = cEmManage_GetSpeedRate(D_005864F0);
    *(float *)(s0 + PHASE_OBJ_RATE) = rate;
    i8 = *(unsigned char *)(s0 + PHASE_OBJ_STATE) * 8;
    e = (char *)&D_003BDDA8 + i8;
    type = *(short *)(e + 2);
    if (type >= 0) {
        int base = *(int *)(s0 + *(short *)(e + 4));
        entry = *(long *)(base + type * 8 - 8);
        fp = (int (*)(int))(int)(entry >> 32);
    } else {
        fp = *(int (**)(int))((char *)&D_003BDDA8 + i8 + 4);
    }
    f0 = D_003BDDA8.e[*(unsigned char *)(s0 + PHASE_OBJ_STATE)].adjust;
    if (type >= 0)
        arg = (short)entry + f0;
    else
        arg = f0;
    fp((int)(s0 + arg));
    func_001B76D8(s0);
}
