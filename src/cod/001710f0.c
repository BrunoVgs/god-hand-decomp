/* sn-2.95.3-136 matched TU. */

#include "godhand/cMovie.h"

extern void func_00345F48(int handle, int mode);
extern void cHeap_free(int, int *);
extern void displayScrollLayer(int a0, int a1);
extern char D_00420CA0[];
extern void func_002AD288(void *sub, int mode);
extern void func_003A52F0(void *dst, int value, int size);

/* cPadVib init: points the table at the default vibration data and stops any running sequence. */
typedef struct cPadVib {
    int table;       /* 0x00 address of the vibration table */
    int seq;         /* 0x04 running sequence id */
    int unk008[2];
    unsigned flags;  /* 0x10 */
} cPadVib;

typedef struct VibHead {
    int unk000;
    int tableOff;    /* 0x04 offset of the table from the head */
} VibHead;

extern VibHead *D_007479F4;
extern void cPadVib_stopSeq(cPadVib *self);

__attribute__((section(".text.cPadVib_init")))
void cPadVib_init(cPadVib *self) {
    self->table = D_007479F4->tableOff + (int)D_007479F4;
    cPadVib_stopSeq(self);
    self->flags |= 1;
}

/* Stops the track's stream player if the player is still running (mode 0). */
__attribute__((section(".text.cMovieTrack_stop")))
void cMovieTrack_stop(cMovieTrack *track) {
    if (track->handle != 0 && func_00345B88(track->handle) != 0) {
        func_00345F48(track->handle, 0);
    }
}

/* Heap-owned buffer holder: releases the buffer (block header word at -0x20 holds the heap handle). */
typedef struct HeapBuf {
    int *buf;        /* 0x00 heap block, or NULL */
    char flag;       /* 0x04 */
} HeapBuf;

extern void func_002BE6C8(HeapBuf *self);


__attribute__((section(".text.HeapBuf_release")))
void HeapBuf_release(HeapBuf *self) {
    func_002BE6C8(self);
    if (self->buf != 0) {
        cHeap_free(self->buf[-8], self->buf);
    }
    self->flag = 0;
    self->buf = 0;
}

/* Callback: when value is 0 and mode is 0 or 4, hides scroll layers 0x1E and 0x1F. */
__attribute__((section(".text.ScrollCallback_hideLayers")))
void ScrollCallback_hideLayers(int mode, float value) {
    if (value == 0.0f) {
        if (mode == 0 || mode == 4) {
            displayScrollLayer(0x1E, 0);
            displayScrollLayer(0x1F, 0);
        }
    }
}

/* Destructor of the object built by func_00171070: reinstalls its vtable, shuts the sub-object, runs the base destructor. */
typedef struct VtObj {
    char unk000[0x214];
    void *vt;                /* 0x214 */
    char unk218[0x1AE0 - 0x218];
    char sub[1];             /* 0x1AE0 sub-object */
} VtObj;



extern void SetField214PtrThenInit_1B6F38(VtObj *self, int flags);

__attribute__((section(".text.VtObj_destroyDerived")))
void VtObj_destroyDerived(VtObj *self, int flags) {
    self->vt = D_00420CA0;
    func_002AD288(self->sub, 2);
    SetField214PtrThenInit_1B6F38(self, flags);
}

/* Clears the three regions of the work area: header, body, tail. */
#define WORK_HEAD_SIZE  0x14A0
#define WORK_BODY_SIZE  0x9C30
#define WORK_TAIL_OFF   0xB0D0
#define WORK_TAIL_SIZE  0x20

typedef struct WorkArea {
    char head[WORK_HEAD_SIZE];                                  /* 0x0000 */
    char body[WORK_BODY_SIZE];                                  /* 0x14A0 */
    char tail[WORK_TAIL_SIZE];                                  /* 0xB0D0 */
} WorkArea;



__attribute__((section(".text.WorkArea_clear")))
void WorkArea_clear(WorkArea *self) {
    func_003A52F0(self->head, 0, WORK_HEAD_SIZE);
    func_003A52F0(self->body, 0, WORK_BODY_SIZE);
    func_003A52F0(self->tail, 0, WORK_TAIL_SIZE);
}
