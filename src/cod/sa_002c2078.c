/* sn-2.95.3-136: func_002C2078, door trigger: looks up the jump target for the door and, unless
 * the door is locked, installs its exit callback once and starts the jump. */
typedef struct {
    char pad0[0x14];
    unsigned short id; /* 0x14 */
} DoorJump;
typedef struct {
    char pad0[2];
    unsigned char room; /* 0x2 */
    char pad3[0x14 - 3];
    void *arg; /* 0x14 */
    void (*func)(void *); /* 0x18 */
    char pad1C;
    unsigned char door; /* 0x1D */
    unsigned char lock; /* 0x1E */
} DoorInfo;
extern int D_00747A24;
extern DoorJump D_00583EC0;
extern void *D_003C2F84;
extern int cDoor_getJumpData(DoorJump *jd, unsigned char door, unsigned char room, unsigned char a, int b, unsigned char c);
extern void cScenario_SetExitFunc(void *self, void (*func)(void *), void *arg);
extern void cDoor_setDoorJump(DoorJump *jd);

__attribute__((section(".text.func_002C2078")))
int func_002C2078(char *obj)
{
    DoorInfo *info = (DoorInfo *)(obj + 0x5C);
    long flags = D_00747A24;
    DoorJump *jd;

    if ((((unsigned long)flags >> 3) & 1UL) == 1UL)
        return 0;
    jd = &D_00583EC0;
    if (cDoor_getJumpData(jd, info->door, info->room, 2, 0, 0) == 0)
        return 0;
    switch (info->lock) {
    case 0:
        break;
    case 1:
        return 0;
    }
    if (info->func != 0) {
        cScenario_SetExitFunc(D_003C2F84, info->func, info->arg);
        if (jd->id != 0xFFFF)
            info->func = 0;
    }
    cDoor_setDoorJump(&D_00583EC0);
    return 0;
}
