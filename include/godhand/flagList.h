/* include/godhand/flagList.h - a counted byte list of flags (func_00382850, func_00383280). */
#ifndef GODHAND_FLAGLIST_H
#define GODHAND_FLAGLIST_H

typedef struct FlagList {
    char unk0[0x8];
    int count;                          /* 0x08 */
    char unkC[0xC];
    unsigned char flag[1];              /* 0x18 flag[1..count] are tested */
} FlagList;

#endif
