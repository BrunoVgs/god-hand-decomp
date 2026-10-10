/* include/godhand/cOmSized.h - a cOmBase object with an extent vector.
 *
 * The record is a cOmBase (0x5E0 bytes) plus an extent vector at 0x600
 * (x, y, z size of the object's hit volume; w is 1.0). The init methods of
 * several objects build the vector on the stack, copy it over, then run the
 * shared setters and set bit 4 of the script flag word at 0x5A0.
 *
 * Field names are ours, taken from the methods that read and write them.
 * Offsets are exact: every body that uses this header builds byte-identical
 * to retail. A field we can't name yet stays as unkNNN padding.
 */
#ifndef GODHAND_COMSIZED_H
#define GODHAND_COMSIZED_H

#include "godhand/cOmBase.h"

#define COMSIZED_SCR_READY  0x10        /* bit set in the flag word at 0x5A0 once the init ran */

typedef struct cOmSized {
    cOmBase base;                       /* 0x000 */
    char unk5E0[0x20];
    cVec extent;                        /* 0x600 */
} cOmSized;

/* The script flag word at 0x5A0 sits inside cOmBase's padding. */
#define COMSIZED_SCRFLAGS(self) (*(int *)((char *)(self) + 0x5A0))

#endif
