/* sn-2.95.3-136 matched TU. */

#include "godhand/cMc.h"
#include "godhand/cEvent.h"
#include "godhand/Slot2.h"

extern void func_0();
extern cMc D_005E6900;
extern cMcTaskRef D_00752C00;
extern void cMc_DllLoad(cMc *self, int pump);
extern void cMc_DllRelease(cMc *self);
extern void cTaskWork_exit(void *task);
extern void Obj0000_Set_D_007474A0_Fields_5D8_5E0(int a0);
extern void cIDBase_release(int a0);
extern void func_00161590(int a0);
extern char **D_003C2384;
extern void displayScrollLayer(int layer, int show);

/* sn-2.95.3-136 */
/* Motion blend record: a table of up to 0x23 halfwords copied in from a source table. */
typedef struct BlendWork {
    char unk00[0x90];
    unsigned int flags;                 /* 0x90 */
    char unk94[0x36C - 0x94];
    short table[0x23];                  /* 0x36C copied from the source table */
    short tableNum;                     /* 0x3B2 halfwords in use, at most 0x23 */
} BlendWork;

#define BLENDWORK_TABLE_READY 0x40000000        /* flags: the table holds fresh data */
#define BLENDWORK_TABLE_MAX   0x23

extern void *func_003A5148(void *d, const void *s, int n); /* memcpy */

/* Copy num halfwords from src into the table (clamped to the table size) and mark the table ready. */
__attribute__((section(".text.func_001450A0")))
void func_001450A0(BlendWork *self, void *src, short num) {
    if (num >= BLENDWORK_TABLE_MAX + 1) {
        self->tableNum = BLENDWORK_TABLE_MAX;
    } else {
        self->tableNum = num;
    }
    func_003A5148(self->table, src, self->tableNum << 1);
    self->flags |= BLENDWORK_TABLE_READY;
}

/* sn-2.95.3-136 */










/* Load the memory card module, run its two stripped log hooks, release it and end the calling task. */
__attribute__((section(".text.func_002AE838")))
void func_002AE838(void) {
    cMc_DllLoad(&D_005E6900, 0);
    func_0(cEvent_nullStr00);
    func_0(cEvent_nullStr00);
    cMc_DllRelease(&D_005E6900);
    cTaskWork_exit(D_00752C00.task);
}

/* sn-2.95.3-136 */





/* Reset an object: run the base reset, release its four id slots, clear two counters on the shared record. */
__attribute__((section(".text.func_001655D8")))
void func_001655D8(int a0) {
    char *p;
    Obj0000_Set_D_007474A0_Fields_5D8_5E0(a0);
    cIDBase_release(a0 + 0x230);
    cIDBase_release(a0 + 0x100);
    cIDBase_release(a0);
    cIDBase_release(a0 + 0x180);
    p = *D_003C2384;
    *(int *)(p + 0x24) = 0;
    *(int *)(p + 0x20) = 0;
    func_00161590(a0);
}

/* sn-2.95.3-136 */




/* Slot2 line mark 2, once a frame: while lit (bit 15), count 8 frames, then flip the shown bit (14) and update the layer. */
#define MARK_BLINK   0x8000     /* markFlag: start lit, counting */
#define MARK_ON      0x4000     /* markFlag: line shown */
#define MARK_COUNT   0x3FFF     /* markFlag: frames since the last flip */
#define MARK_PERIOD  8

__attribute__((section(".text.func_001E6DA0")))
void func_001E6DA0(Slot2 *self) {
    unsigned int flag = self->markFlag[2];
    if (flag & MARK_BLINK) {
        unsigned short next;    /* short: the store keeps retail's andi 0xFFFF */
        flag = flag + 1;
        self->markFlag[2] = flag;
        if ((flag & MARK_COUNT) >= MARK_PERIOD) {
            next = (~flag & MARK_ON) | MARK_BLINK;
            self->markFlag[2] = next;
            if (next & MARK_ON) {
                displayScrollLayer(self->lineLayer, 1);
            } else {
                displayScrollLayer(self->lineLayer, 0);
            }
        }
    }
}

/* sn-2.95.3-136 */




/* Slot2 line mark 3, once a frame: while lit (bit 15), count 8 frames, then flip the shown bit (14) and update the layer. */
#define MARK_BLINK   0x8000     /* markFlag: start lit, counting */
#define MARK_ON      0x4000     /* markFlag: line shown */
#define MARK_COUNT   0x3FFF     /* markFlag: frames since the last flip */
#define MARK_PERIOD  8

__attribute__((section(".text.func_001E6E68")))
void func_001E6E68(Slot2 *self) {
    unsigned int flag = self->markFlag[3];
    if (flag & MARK_BLINK) {
        unsigned short next;    /* short: the store keeps retail's andi 0xFFFF */
        flag = flag + 1;
        self->markFlag[3] = flag;
        if ((flag & MARK_COUNT) >= MARK_PERIOD) {
            next = (~flag & MARK_ON) | MARK_BLINK;
            self->markFlag[3] = next;
            if (next & MARK_ON) {
                displayScrollLayer(self->lineLayer, 1);
            } else {
                displayScrollLayer(self->lineLayer, 0);
            }
        }
    }
}

/* sn-2.95.3-136 */


/* The scroll-layer mark at 0x4A8 of the Slot2 object; the fields are not in Slot2.h yet. */
typedef struct Slot2Mark {
    char unk00[0x430];
    int markLayer;                      /* 0x430 layer shown for this mark */
    char unk434[0x4A8 - 0x434];
    unsigned short markFlag;            /* 0x4A8 bit 15 = start lit, bit 14 = on */
} Slot2Mark;

#define MARK_BLINK   0x8000     /* markFlag: start lit, counting */
#define MARK_ON      0x4000     /* markFlag: line shown */
#define MARK_COUNT   0x3FFF     /* markFlag: frames since the last flip */
#define MARK_PERIOD  8

/* Mark at 0x4A8, once a frame: while lit (bit 15), count 8 frames, then flip the shown bit (14) and update the layer. */
__attribute__((section(".text.func_001E3DD0")))
void func_001E3DD0(Slot2Mark *self) {
    unsigned int flag = self->markFlag;
    if (flag & MARK_BLINK) {
        unsigned short next;    /* short: the store keeps retail's andi 0xFFFF */
        flag = flag + 1;
        self->markFlag = flag;
        if ((flag & MARK_COUNT) >= MARK_PERIOD) {
            next = (~flag & MARK_ON) | MARK_BLINK;
            self->markFlag = next;
            if (next & MARK_ON) {
                displayScrollLayer(self->markLayer, 1);
            } else {
                displayScrollLayer(self->markLayer, 0);
            }
        }
    }
}
