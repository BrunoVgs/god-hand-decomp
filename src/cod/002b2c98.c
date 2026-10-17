/* sn-2.95.3-136 matched TU. */

#define EVENT_FLAG_CUT_ACTIVE 0x20000000        /* D_00747A84 bit: a cutscene is running */

/* The cut record an event step points at: its end frame at +2. */
typedef struct CutRange {
    char unk00[2];
    unsigned short endFrame;            /* 0x02 */
} CutRange;

typedef struct CutStep {
    char unk00[0x8C];
    CutRange *range;                    /* 0x8C */
} CutStep;

extern unsigned int D_00747A84;
extern char D_00586AF0[];
extern float cEvent_getCutFrame();

/* Nonzero while a cutscene runs and the current cut frame is still short of this step's end frame. */
__attribute__((section(".text.func_002B2C98")))
int func_002B2C98(CutStep *self)
{
    float frame;

    if ((D_00747A84 & EVENT_FLAG_CUT_ACTIVE) == 0)
        return 0;
    frame = cEvent_getCutFrame(D_00586AF0);
    if ((float)self->range->endFrame <= frame)
        return 0;
    return 1;
}
