/* include/godhand/Sfd.h - Sofdec movie player records.
 *
 * A Sofdec handle keeps its track table at 0x1310, one 0x74-byte SfdTrack per
 * track number. A track that is set up has a nonzero `ready` word. Names are
 * ours; unnamed fields stay as unkNN padding.
 */
#ifndef GODHAND_SFD_H
#define GODHAND_SFD_H

#define SFD_ERR_TRACK_NOT_READY  0xFF000401  /* error raised for a track that is not set up */
#define SFD_TRIF_IDLE_CALL       0xB         /* track-interface call made on a track that is not set up */

typedef struct SfdTrack {
    int unk00;                          /* 0x00 */
    int ready;                          /* 0x04 nonzero once the track is set up */
    char unk08[0xC];
    void *obj;                          /* 0x14 the track's object */
    char unk18[0x34];
    int type;                           /* 0x4C track type, selects the track interface */
    char unk50[0x24];
} SfdTrack;                             /* 0x74 */

typedef struct SfdHandle {
    char unk0000[0x1310];
    SfdTrack track[1];                  /* 0x1310 indexed by track number */
} SfdHandle;

#endif
