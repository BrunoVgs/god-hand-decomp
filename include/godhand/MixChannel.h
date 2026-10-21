/* include/godhand/MixChannel.h - a per-channel level set.
 *
 * Two level arrays sit side by side: entry 0 holds the value in use, entries
 * 1..chCount the per-channel values. `sel` is the 1-based channel whose value
 * applies, 0 for none. Names are ours; unnamed fields stay as padding.
 */
#ifndef GODHAND_MIXCHANNEL_H
#define GODHAND_MIXCHANNEL_H

typedef struct MixChannel {
    char unk00[4];
    unsigned char sel;                  /* 0x04 */
    char unk05[0x17];
    short levelA[5];                    /* 0x1C */
    short levelB[67];                   /* 0x26 */
    int chCount;                        /* 0xAC */
} MixChannel;

#endif
