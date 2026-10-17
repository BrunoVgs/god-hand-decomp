/* sn-2.95.3-136 matched TU. */

#include "godhand/ScenarioCursor.h"

extern void func_002BF708(ScenarioCursor *self);
extern void SysFlags_saveAndFreeze(ScenarioCursor *self);
extern void func_002C09E8(void *p);
extern void *D_003C264C;
extern char D_0044F1C8[];
extern void ReleaseObj(void *obj);
extern void func_002FBE28(void *self, int flags);
extern void func_002D5790(void *work);
extern void cIDBase_restartAnim(void *self);
extern void *cIDBase_getIDWork(void *self, int idx);

/* Re-initialise a second scenario cursor: run the two reset steps, tell the manager,
 * then set its four state bytes (step = 2, keep = old keep value, rest 0). */
__attribute__((section(".text.ScenarioCursor_reinitStep2")))
void ScenarioCursor_reinitStep2(ScenarioCursor *self) {
    func_002BF708(self);
    SysFlags_saveAndFreeze(self);
    func_002C09E8(D_003C264C);
    {
        char old = self->keep;
        self->step = 2;
        self->keep = old;
        self->unk02 = 0;
        self->unk03 = 0;
    }
}

/* An object with a method table at 0xF0 that owns another object at 0x2B0. */
typedef struct OwnerObj {
    char unk000[0xF0];
    void *vt;                           /* 0xF0 */
    char unkF4[0x1BC];
    void *owned;                        /* 0x2B0 */
} OwnerObj;





/* Destructor of the object with vtable D_0044F1C8: reset the vtable, release
 * the owned object at +0x2B0 if any, then run the base destructor. */
__attribute__((section(".text.OwnerObj_destroyOwned2")))
void OwnerObj_destroyOwned2(OwnerObj *self, int flags) {
    self->vt = D_0044F1C8;
    if (self->owned != 0)
        ReleaseObj(self->owned);
    func_002FBE28(self, flags);
}

#define POOL_WORK_SIZE 0x58

typedef struct TaskPool {
    char *works;                        /* 0x00 */
    char unk04[8];
    unsigned short count;               /* 0x0C */
} TaskPool;



/* Run func_002D5790 on every work record of a pool: works array at +0, count at +0xC. */
__attribute__((section(".text.TaskPool_runAll")))
void TaskPool_runAll(TaskPool *self) {
    unsigned int i;
    for (i = 0; i < self->count; i++)
        func_002D5790(self->works + i * POOL_WORK_SIZE);
}

#define ENTRY_COUNT 3

typedef struct IdScreen3 {
    char unk00[0x1C];
    unsigned char started;              /* 0x1C */
    char unk1D[0x73];
    void *ent[ENTRY_COUNT];             /* 0x90 */
} IdScreen3;




/* Restart the animation and refill the 3 entry pointers at 0x90 from cIDBase_getIDWork. */
__attribute__((section(".text.IdScreen3_refillEntries")))
void IdScreen3_refillEntries(IdScreen3 *self) {
    unsigned short i = 0;
    cIDBase_restartAnim(self);
    self->started = 1;
    do {
        self->ent[i] = cIDBase_getIDWork(self, i);
        i = i + 1;
    } while (i < ENTRY_COUNT);
}

#define ENTRY_COUNT 4

typedef struct IdScreen4 {
    char unk00[0x1C];
    unsigned char started;              /* 0x1C */
    char unk1D[0x73];
    int unk90;                          /* 0x90 */
    int sel;                            /* 0x94 */
    void *ent[ENTRY_COUNT];             /* 0x98 */
} IdScreen4;




/* Restart the animation and refill the 4 entry pointers at 0x98 from
 * cIDBase_getIDWork, then clear the selection word at 0x94. */
__attribute__((section(".text.IdScreen4_refillEntries")))
void IdScreen4_refillEntries(IdScreen4 *self) {
    unsigned short i = 0;
    self->unk90 = 0;
    cIDBase_restartAnim(self);
    self->started = 1;
    do {
        self->ent[i] = cIDBase_getIDWork(self, i);
        i = i + 1;
    } while (i < ENTRY_COUNT);
    self->sel = 0;
}
