/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"

extern float cEmManage_GetSpeedRate(void *manager);
extern unsigned short GetField_BEE_2B1290(void);
extern void func_002AFED0(void *self, int a, int b, int c, float x, float y);
extern int cOl30_SetInitialPosition(void *self, void *dst, void *pos);

typedef struct InitRec {
    int state;                          /* 0x00 */
    int mode;                           /* 0x04 */
    int unk08;
    int result;                         /* 0x0C return of func_003078E0(src) */
    int param;                          /* 0x10 */
    char unk14[0xC];
    int src;                            /* 0x20 */
} InitRec;

/* Start the record: mode 1, convert the source, keep the parameter, state 2. */
__attribute__((section(".text.InitRec_start")))
void InitRec_start(InitRec *self, int src, int param)
{
    self->mode = 1;
    self->result = func_003078E0(src);
    self->param = param;
    self->src = src;
    self->state = 2;
}

extern int D_005864F0;                  /* enemy manager */

/* An object with a countdown past cOmBase. */
typedef struct CountdownObj {
    cOmBase base;                       /* 0x000 */
    char unk5E0[0x50];
    float timeLeft;                     /* 0x630 */
} CountdownObj;

/* Count the timer down by the frame rate while it is positive; returns 1 once it is spent. */
__attribute__((section(".text.CountdownObj_tickIsSpent")))
int CountdownObj_tickIsSpent(CountdownObj *self)
{
    float rate = cEmManage_GetSpeedRate(&D_005864F0);
    if (self->timeLeft > 0.0f) {
        self->timeLeft -= rate;
    }
    return self->timeLeft <= 0.0f;
}

typedef struct PosObj {
    char unk00[0x1C];
    int endTime;                        /* 0x1C */
    char unk20[0x4C];
    int startTime;                      /* 0x6C */
    char unk70[0x18];
    float posX;                         /* 0x88 */
    float posY;                         /* 0x8C */
} PosObj;

/* Forward the object, the current field value and the elapsed span to func_002AFED0 together with the two position floats. */
__attribute__((section(".text.PosObj_forwardSpan")))
void PosObj_forwardSpan(PosObj *self, int arg)
{
    int span = self->endTime - self->startTime;
    int field = GetField_BEE_2B1290();
    func_002AFED0(self, field, arg, span, self->posX, self->posY);
}

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct cOl30Obj {
    char unk000[0xF0];
    Vec3 *target;                       /* 0x0F0 vector kept in step with pos */
    char unkF4[0xC];
    Vec3 initPos;                       /* 0x100 */
    char unk10C[0x384];
    Vec3 pos;                           /* 0x490 */
} cOl30Obj;

/* Set pos from src (when it is not already pos), mirror it into target, then place the object at its initial position. */
__attribute__((section(".text.cOl30_setPosAndPlace")))
void cOl30_setPosAndPlace(cOl30Obj *self, Vec3 *src)
{
    Vec3 *pos = &self->pos;
    Vec3 *dst;
    if (pos != src) {
        self->pos.x = src->x;
        pos->y = src->y;
        pos->z = src->z;
    }
    dst = self->target;
    if (dst != pos) {
        dst->x = self->pos.x;
        dst->y = pos->y;
        dst->z = pos->z;
    }
    cOl30_SetInitialPosition(self, self->target, &self->initPos);
}

#define POOLENT_SIZE  0x480     /* sizeof one pool entry */

typedef struct EntPool {
    char unk00[0x1C];
    unsigned int used;                  /* 0x1C entries in use */
    char unk20[4];
    unsigned int usedMin;               /* 0x24 lowest value of used seen so far */
} EntPool;

/* Take an entry from the pool, count it, clear it and run its initialiser. Returns 0 when the pool is empty. */
__attribute__((section(".text.EntPool_allocClear")))
void *EntPool_allocClear(EntPool *self)
{
    int ent = func_002A97A0(self);
    unsigned int n;

    if (ent == 0) {
        return 0;
    }
    n = self->used - 1;
    self->used = n;
    if (n < self->usedMin) {
        self->usedMin = n;
    }
    func_003A52F0((void *)ent, 0, POOLENT_SIZE);
    return func_00148358((void *)ent);
}

extern unsigned int D_00747A78;         /* system flags */

typedef struct { char b[8]; } SysFlags8;

typedef struct FlagSaveObj {
    char unk00[0x74];
    SysFlags8 saved;                    /* 0x74 copy of the system flag words */
} FlagSaveObj;

/* Save the system flag words in the object, then set the flags for the frozen state. */
__attribute__((section(".text.SysFlags_saveAndFreeze")))
void SysFlags_saveAndFreeze(FlagSaveObj *self)
{
    self->saved = *(SysFlags8 *)&D_00747A78;
    D_00747A78 &= 0xFDFFFFFF;
    D_00747A78 |= 0x80000000;
    D_00747A78 |= 0x40000000;
    D_00747A78 |= 0x80000000;
    D_00747A78 |= 0x20000;
    D_00747A78 |= 0x10002000;
    D_00747A78 |= 0x40000;
    D_00747A78 |= 0x8000000;
    D_00747A78 |= 0x800000;
}
