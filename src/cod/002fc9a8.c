/* sn-2.95.3-136 matched TU. */

typedef struct StepRec {
    int unk00;
    unsigned int flags;         /* 0x04 bit 0x2000: step on its own */
} StepRec;

/* A stepping object: a frame counter (float, 0x234) with a limit (0x238) and its integer copy (0x22E). */
typedef struct StepObj {
    char unk000[0x110];
    StepRec *rec;               /* 0x110 */
    char unk114[8];
    unsigned int flags;         /* 0x11C bit 0x800: loops, 0x400: restarts at 0 */
    char unk120[0x22E - 0x120];
    short frame;                /* 0x22E */
    char unk230[4];
    float time;                 /* 0x234 */
    short limit;                /* 0x238 */
} StepObj;

extern unsigned int D_00747A84;
extern void func_002FA350(float *time);
extern void UpdateObjByIndexedOp_2FBE50(StepObj *self);

/* Hold the time when the step is held (D_00747A84 bit 0x20000, or a held object), else advance it by 1.0. */
#define STEP_TIME(self) \
    do { \
        if ((((self)->rec->flags & 0x2000) == 0 && (*(unsigned char *)((char *)(self) + 0x11D) & 1) != 0) \
            || (D_00747A84 & 0x20000) != 0) { \
            func_002FA350(&(self)->time); \
        } else { \
            (self)->time = (self)->time + 1.0f; \
        } \
    } while (0)

/* func_002FC9A8: advance the frame counter. At the limit it either wraps (flag 0x800: back to 0 or the limit)
 * or hands over to UpdateObjByIndexedOp (returns 1). The time steps by 1.0 or is held, and the frame is the
 * time truncated. Returns 0. */
__attribute__((section(".text.func_002FC9A8")))
int func_002FC9A8(StepObj *self)
{
    short limit;
    unsigned int fl;
    limit = self->limit;
    if (limit <= 0) {
        STEP_TIME(self);
    } else {
        if (self->frame >= limit) {
            fl = self->flags;
            if ((fl & 0x800) != 0) {
                if ((fl & 0x400) != 0) {
                    self->frame = 0;
                } else {
                    self->frame = self->limit;
                }
            } else {
                UpdateObjByIndexedOp_2FBE50(self);
                return 1;
            }
        }
        STEP_TIME(self);
    }
    self->frame = (int)self->time;
    return 0;
}
