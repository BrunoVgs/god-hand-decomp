/* sn-2.95.3-136 matched TU. */

#define SNDGRP_ENTRIES   2              /* sound entries per group */

typedef struct SoundRec {
    unsigned short f0;                  /* 0x00 sound id */
    unsigned short f2;
    unsigned short f4;
    unsigned short f6;
    unsigned short f8;
    unsigned short fA;
    int fC;                             /* 0x0C mask word */
} SoundRec;

typedef struct SoundGroupEnt {          /* D_0044CCC0 rows: 2 entries per group, 0xC each */
    unsigned short f0, f2, f4, f6, f8, fA;
} SoundGroupEnt;

typedef struct SoundOwner {
    char unk000[0x130];
    int group;                          /* 0x130 sound group loaded now */
} SoundOwner;

extern SoundGroupEnt D_0044CCC0[][SNDGRP_ENTRIES];
extern int D_0044CE40[SNDGRP_ENTRIES];
extern int StoreSoundEntry_3749D8(short slot, SoundRec *rec);

/* Load a sound group: copy each of the group's two entries to a stack record, add its mask word and store it into the sound table; stop at the first failure, else remember the group. */
__attribute__((section(".text.func_002CA390")))
void func_002CA390(SoundOwner *self, int group)
{
    SoundRec rec[2];                    /* retail reserves 0x20 bytes for the record; only [0] is used */
    int i;
    SoundGroupEnt *src;
    int *mask;
    if (self->group == group) {
        return;
    }
    src = D_0044CCC0[group];
    mask = D_0044CE40;
    for (i = 0; i < SNDGRP_ENTRIES; i++, mask++, src++) {
        rec[0].f0 = src->f0;
        rec[0].f2 = src->f2;
        rec[0].f4 = src->f4;
        rec[0].f6 = src->f6;
        rec[0].f8 = src->f8;
        rec[0].fA = src->fA;
        rec[0].fC = *mask;
        if (StoreSoundEntry_3749D8(i, &rec[0]) == -1) {
            return;
        }
    }
    self->group = group;
}
