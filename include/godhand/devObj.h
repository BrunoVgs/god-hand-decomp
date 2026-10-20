/* include/godhand/devObj.h - the device object programmed and read back by the cygnus code at
 * 0x36C6C8..0x36C790.
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_DEVOBJ_H
#define GODHAND_DEVOBJ_H

/* One channel's three parameter words. */
typedef struct DevChParam {
    int a;                      /* 0x0 */
    int b;                      /* 0x4 */
    int c;                      /* 0x8 */
} DevChParam;

/* The device status block read back into the object. */
typedef struct DevStat {
    char data[0x80];
} DevStat;

typedef struct DevObj {
    char unk000[0x1D0];
    DevStat stat;               /* 0x1D0 */
    char unk250[0x2A8 - 0x250];
    int a;                      /* 0x2A8 */
    int blocks;                 /* 0x2AC */
    char unk2B0[4];
    int d;                      /* 0x2B4 */
    int e;                      /* 0x2B8 */
    int c;                      /* 0x2BC */
    char unk2C0[0x3B4 - 0x2C0];
    int dev;                    /* 0x3B4 */
    int unk3B8;                 /* 0x3B8 */
    DevChParam ch[4];           /* 0x3BC */
    int p0;                     /* 0x3EC */
    int p1;                     /* 0x3F0 */
    char unk3F4[4];
} DevObj;

#endif /* GODHAND_DEVOBJ_H */
