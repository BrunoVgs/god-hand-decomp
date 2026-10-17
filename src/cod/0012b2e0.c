/* sn-2.95.3-136 matched TU. */

#include "godhand/cCoreSave.h"
#include "godhand/cRecordIndex.h"
#include "godhand/cMessage.h"

extern int cOmWeapon_SetDamage(void *weapon);
extern void cOmWeapon_SetBreak(void *weapon);
extern void func_002B2400(cMessageWin *win);
extern void BufHolder_deletingDtor(void *entry, int mode);
extern void __builtin_delete(void *p);

/* True when the skill that slot i of the index points at is at level 1.
 * False while the index has no table. */
__attribute__((section(".text.cRecordIndex_isSlotSkillLevel1")))
int cRecordIndex_isSlotSkillLevel1(cRecordIndex *self, int i)
{
    if (self->table == 0)
        return 0;
    return cCoreSave_getSkill(&D_00569B70, self->index[i]) == 1;
}

/* Object that carries one weapon: the handle sits at 0x698. */
typedef struct WeaponCarrier {
    char unk000[0x698];
    void *weapon;                       /* 0x698 carried weapon, 0 = none */
} WeaponCarrier;




/* Apply damage to the carried weapon; when that wrecks it, break it and let go. */
__attribute__((section(".text.WeaponCarrier_damageHeldWeapon")))
void WeaponCarrier_damageHeldWeapon(WeaponCarrier *self)
{
    if (self->weapon != 0 && cOmWeapon_SetDamage(self->weapon) != 0) {
        cOmWeapon_SetBreak(self->weapon);
        self->weapon = 0;
    }
}

#define CMESSAGEWIN_MESSNO_OFFSET 0x2C  /* byte: message number shown in the window */



/* Close every open window that shows message messNo. */
__attribute__((section(".text.cMessage_closeMessNo8")))
void cMessage_closeMessNo8(cMessage *self, int messNo)
{
    cMessageWin *win;
    unsigned char no = messNo;

    for (win = self->head; win != 0; win = win->next) {
        if (*(unsigned char *)((char *)win + CMESSAGEWIN_MESSNO_OFFSET) == no)
            func_002B2400(win);
    }
}

/* A list that counts the entries it has released. */
typedef struct EntCounter {
    char unk00[0x1C];
    int released;                       /* 0x1C */
} EntCounter;


extern void func_002A9800(EntCounter *list, void *entry);

/* Destroy entry (mode 2), count it, then hand it back to the list. */
__attribute__((section(".text.EntCounter_releaseEntry")))
void EntCounter_releaseEntry(EntCounter *list, void *entry)
{
    if (entry != 0) {
        list->released++;
        BufHolder_deletingDtor(entry, 2);
        func_002A9800(list, entry);
    }
}

#define SLOT_NUM 8

/* An owner of eight heap objects at 0x74. */
typedef struct SlotOwner {
    char unk00[0x74];
    void *slot[SLOT_NUM];               /* 0x74 */
} SlotOwner;



/* Free each of the eight objects and clear its handle. */
__attribute__((section(".text.SlotOwner_freeSlots")))
void SlotOwner_freeSlots(SlotOwner *self)
{
    unsigned int i;

    for (i = 0; i < SLOT_NUM; i++) {
        if (self->slot[i] != 0) {
            __builtin_delete(self->slot[i]);
            self->slot[i] = 0;
        }
    }
}

#define STEP_KIND_A 1
#define STEP_KIND_B 2

/* A step record: the kind byte at +1 chooses which handler runs. */
typedef struct StepRec {
    char unk00;
    signed char kind;                   /* 0x01 */
} StepRec;

extern void ScenarioCursor_reinitStep2(StepRec *rec);
extern void func_002BF518(StepRec *rec);

/* Run the handler for the record's kind; other kinds do nothing. */
__attribute__((section(".text.StepRec_runKindHandler")))
void StepRec_runKindHandler(StepRec *rec)
{
    switch (rec->kind) {
    case STEP_KIND_A:
        ScenarioCursor_reinitStep2(rec);
        break;
    case STEP_KIND_B:
        func_002BF518(rec);
        break;
    }
}
