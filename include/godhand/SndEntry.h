/* include/godhand/SndEntry.h - the sound voice and sound event tables.
 *
 * The voice table holds SND_VOICE_NUM 0x40-byte entries, the event table
 * SND_EVENT_NUM 0x50-byte entries. An entry is live while `active` is
 * nonzero. Names are ours; unnamed fields stay as padding.
 */
#ifndef GODHAND_SNDENTRY_H
#define GODHAND_SNDENTRY_H

#define SND_VOICE_NUM         0x60
#define SND_VOICE_FLAG_SKIP   0x10   /* SndVoice.flags: ignored by the id search */

typedef struct SndVoice {
    unsigned short active;              /* 0x00 */
    short unk02;
    int id;                             /* 0x04 0 matches any voice */
    unsigned char flags;                /* 0x08 */
    char unk09[0x37];
} SndVoice;                             /* 0x40 */

#define SND_EVENT_NUM    51
#define SND_EVENT_REQ_1  1       /* request: set SND_EVENT_BITS_1 */
#define SND_EVENT_REQ_2  2       /* request: set SND_EVENT_BITS_2 */
#define SND_EVENT_BITS_1 0x9
#define SND_EVENT_BITS_2 0xA

typedef struct SndEvent {
    unsigned short active;              /* 0x00 */
    char unk02[3];
    unsigned char group;                /* 0x05 group bits, matched against a mask */
    unsigned short flags;               /* 0x06 */
    char unk08[0x48];
} SndEvent;                             /* 0x50 */

#endif
