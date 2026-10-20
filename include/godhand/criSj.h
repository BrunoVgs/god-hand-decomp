/* include/godhand/criSj.h - CRI stream joint (SJ) interface and the Sofdec SJ helpers.
 *
 * Field names are ours; vtable offsets are exact.
 */
#ifndef GODHAND_CRISJ_H
#define GODHAND_CRISJ_H

typedef struct SjChunk {
    unsigned char *ptr;         /* 0x00 */
    int len;                    /* 0x04 */
} SjChunk;

typedef struct SjObj SjObj;

typedef struct SjIf {
    void *unk00[5];
    void (*reset)(SjObj *sj);                                   /* 0x14 */
    void (*getChunk)(SjObj *sj, int id, int len, SjChunk *ck);  /* 0x18 */
    void (*ungetChunk)(SjObj *sj, int id, SjChunk *ck);         /* 0x1C */
    void (*putChunk)(SjObj *sj, int id, SjChunk *ck);           /* 0x20 */
    int (*getNumData)(SjObj *sj, int id);                       /* 0x24 */
} SjIf;

struct SjObj {
    SjIf *vt;
};

/* Sofdec stream-joint position feed (0x327818..). */
extern int GetVia4_Obj33C8_GetField_28_7818_327818(void *sj);
extern int func_00327830(void *sj);
extern int GetVia4_Obj33C8_GetField_30_7860_327860(void *sj);
extern int Forward33CFB8_327970(void *sj);
extern void Forward33CFF8_327988(void *sj);
extern void Obj3270_SetField_34(void *sj, int v);
extern void Obj3270_SetField_3C(void *sj, int v);
extern void Obj3270_SetField_40(void *sj, int v);
extern void Obj3270_SetField_44(void *sj, int v);
extern void Obj3270_SetField_48_4C(void *sj, void (*fn)(char *), void *arg);
extern void func_0033F130(const char *msg);

#endif /* GODHAND_CRISJ_H */
