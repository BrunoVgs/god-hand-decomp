/* WaveObj: the ripple object. Its settings come from the record at 0x110
 * (the object's parameter block): wave width, wave height, strength and
 * entry count are copied into the object, then the wave table is filled. */
#ifndef GODHAND_WAVEOBJ_H
#define GODHAND_WAVEOBJ_H

#define WAVE_TABLE_MAX     0x20     /* most entries the wave table holds */
#define WAVE_COUNT_DEFAULT 25       /* entry count used when the record gives 0 or less */
#define WAVE_WIDTH_DEFAULT 25.0f    /* width used when the record gives 0 */
#define WAVE_STEP_DEFAULT  1.0f     /* step used when the record gives 0 */

/* The parameter block pointed to by WaveObj.param. */
typedef struct WaveParam {
    char unk000[0x13C];
    float width;                        /* 0x13C */
    float step;                         /* 0x140 */
    char unk144[0x28];
    int mode;                           /* 0x16C copied to WaveObj.mode */
    int count;                          /* 0x170 copied to WaveObj.count */
} WaveParam;

typedef struct WaveObj {
    char unk000[0x110];
    WaveParam *param;                   /* 0x110 */
    char unk114[0x19C];
    int mode;                           /* 0x2B0 */
    float width;                        /* 0x2B4 */
    float step;                         /* 0x2B8 */
    int count;                          /* 0x2BC table entries to fill */
} WaveObj;

typedef char WaveParam_chk_width[((int)&((WaveParam *)0)->width) == 0x13C ? 1 : -1];
typedef char WaveParam_chk_count[((int)&((WaveParam *)0)->count) == 0x170 ? 1 : -1];
typedef char WaveObj_chk_param[((int)&((WaveObj *)0)->param) == 0x110 ? 1 : -1];
typedef char WaveObj_chk_count[((int)&((WaveObj *)0)->count) == 0x2BC ? 1 : -1];

#endif
