/* include/godhand/ScenarioCursor.h - the four state bytes of a scenario cursor.
 *
 * A scenario cursor is a 4 byte record. Byte 1 is the step selector: 0 means
 * the cursor still has to be re-initialised, 1 means it runs, 2 is the state
 * that cScenarioCursor_reinit leaves behind in the second variant.
 * Byte 0 survives a reinit (it is read and written back), bytes 2 and 3 are
 * cleared.
 *
 * Field names are ours, taken from the methods that read and write them.
 * Offsets are exact: every body that uses this header builds byte-identical
 * to retail. A field we can't name yet stays as unkNNN padding.
 */
#ifndef GODHAND_SCENARIOCURSOR_H
#define GODHAND_SCENARIOCURSOR_H

#define SCENARIOCURSOR_STEP_REINIT  0   /* the step byte asks for a re-initialisation */
#define SCENARIOCURSOR_STEP_RUN     1   /* the cursor is running */

typedef struct ScenarioCursor {
    char keep;                          /* 0x00 survives a reinit unchanged */
    char step;                          /* 0x01 SCENARIOCURSOR_STEP_* */
    char unk02;                         /* 0x02 cleared by a reinit */
    char unk03;                         /* 0x03 cleared by a reinit */
} ScenarioCursor;

typedef char ScenarioCursor_size_check[(sizeof(ScenarioCursor) == 4) ? 1 : -1];

#endif
