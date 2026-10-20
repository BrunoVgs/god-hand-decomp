/* sn-2.95.3-136: func_0037AB00, state hook for the actor's sound slot at +0x12C (loop flag / replay event). */
typedef struct {
    char pad0[0xA];
    short pending;           /* 0x0A */
    char padC[2];
    unsigned short flags;    /* 0x0E */
    char pad10[0x26 - 0x10];
    signed char loop;        /* 0x26 */
} SndSlot;

typedef struct {
    char pad0[0xC];
    void *snd;               /* 0x0C */
    char pad10[0x25 - 0x10];
    signed char state;       /* 0x25 */
    char pad26[0x12C - 0x26];
    SndSlot slot;            /* 0x12C */
} SndActor;

extern int GetSoundEntryStatus_375EF8(void *snd);
extern int BuildSoundEventCd0_375CD0(void *snd, SndSlot *slot);

__attribute__((section(".text.func_0037AB00")))
void func_0037AB00(SndActor *a)
{
    SndSlot *s = &a->slot;

    switch (a->state) {
    case 3:
        if (a->snd != 0 && GetSoundEntryStatus_375EF8(a->snd) != 0) {
            s->pending = 1;
            BuildSoundEventCd0_375CD0(a->snd, s);
        }
        break;
    case 10:
        if (s->loop == -1)
            s->flags |= 1;
        else
            s->flags &= ~1;
        break;
    }
}
