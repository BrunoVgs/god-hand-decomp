/* include/godhand/mwsfd.h - Sofdec (MWSFD) handle views used by the cygnus code at 0x347008..
 *
 * Field names are ours; offsets are exact. The SFX side stores its converted
 * values as an enum and the decoder side keeps three pointer-typed words, so
 * the copies between them don't alias; retail schedules them that way.
 */
#ifndef GODHAND_MWSFD_H
#define GODHAND_MWSFD_H

#define SFD_CH_NONE 8

/* Frame info as the decoder hands it over (at 0x88 of the handle). */
typedef struct MwsfdFrmInf {
    unsigned int fmtA;          /* 0x00 */
    unsigned int fmtB;          /* 0x04 */
    void *w08;
    void *w0C;
    void *w10;
    unsigned int flagA;         /* 0x14 */
    unsigned int flagB;         /* 0x18 */
} MwsfdFrmInf;

typedef struct MwsfdHn {
    char unk00[0x88];
    MwsfdFrmInf frm;            /* 0x88 */
} MwsfdHn;

typedef enum { MWSFSFX_VAL_0 } MwsfsfxVal;

typedef struct MwsfsfxFrmInf {
    MwsfsfxVal fmtA;            /* 0x00 */
    MwsfsfxVal fmtB;            /* 0x04 */
    void *w08;
    void *w0C;
    void *w10;
    MwsfsfxVal flagA;           /* 0x14 */
    MwsfsfxVal flagB;           /* 0x18 */
} MwsfsfxFrmInf;

typedef struct MwsfsfxFrm {
    char unk00[0x60];
    MwsfsfxFrmInf frm;          /* 0x60 */
} MwsfsfxFrm;

/* Channel ids of a playback handle; SFD_CH_NONE if unused. */
typedef struct SfdChSet {
    char unk00[0x14];
    int chB;                    /* 0x14 */
    int chA;                    /* 0x18 */
    int chC;                    /* 0x1C */
} SfdChSet;

typedef struct SfdBufInf {
    char unk00[0xC];
    int minFill;                /* 0xC */
} SfdBufInf;

typedef struct SfdBufCfg {
    char unk00[0x58];
    int maxFill;                /* 0x58 */
} SfdBufCfg;

typedef struct SfdHn {
    char unk0000[8];
    int fill;                   /* 0x0008 */
    char unk000C[0xA0C - 0xC];
    SfdBufCfg cfg;              /* 0x0A0C */
    char unk0A68[0x1F74 - 0xA68];
    SfdChSet ch;                /* 0x1F74 */
} SfdHn;

extern void MWSFSVM_Error(char *s);
extern int func_0034CA30(SfdHn *hn, int ch);
extern void func_0034CA00(SfdHn *hn, int ch, int arg);
extern SfdBufInf *func_0034E988(SfdHn *hn);
extern int func_0034C7F0(SfdHn *hn, int arg);

#endif
