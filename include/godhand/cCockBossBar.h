/* include/godhand/cCockBossBar.h - cCockBossBar, the boss health bar of the cockfight.
 *
 * cCockBossBar is a cIDBase display object. roomInit loads the bar's
 * message pack for the room (once, through the disc reader), initialises
 * the display and looks up five display entries by id into `ent`.
 *
 * Method names are the game's own, from the symbol table in the retail ELF.
 * Field names are ours, taken from the methods that read and write them.
 * Offsets are exact: every body that uses this header builds byte-identical
 * to retail. A field we can't name yet stays as unkNNN padding.
 */
#ifndef GODHAND_CCOCKBOSSBAR_H
#define GODHAND_CCOCKBOSSBAR_H

#include "godhand/cIDBase.h"

#define COCKBOSSBAR_ENT_NUM   5
#define COCKBOSSBAR_MSG_PACK  3         /* message pack number of the bar */

typedef struct cCockBossBar {
    cIDBaseObj base;                    /* 0x00 */
    char unk48[0x94 - sizeof(cIDBaseObj)];
    void *data;                         /* 0x94 the loaded message pack, 0 before the first load */
    int readId;                         /* 0x98 disc read request */
    char unk9C[4];
    unsigned int unkA0;                 /* 0xA0 set to 0x20000000 by roomInit */
    float unkA4;                        /* 0xA4 set to 1.0 by roomInit */
    char unkA8[0xB4 - 0xA8];
    short unkB4;                        /* 0xB4 cleared by roomInit */
    char unkB6[2];
    int unkB8;                          /* 0xB8 cleared by roomInit */
    cIDBaseEnt *ent[COCKBOSSBAR_ENT_NUM];   /* 0xBC display entries looked up by id 0..4 */
} cCockBossBar;

typedef char cCockBossBar_ent_check[(int)&((cCockBossBar *)0)->ent == 0xBC ? 1 : -1];

#endif
