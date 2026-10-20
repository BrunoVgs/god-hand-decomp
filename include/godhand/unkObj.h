/* include/godhand/unkObj.h - partial views of objects whose class is not
 * identified yet. Each names only the fields its users touch; fold them into
 * the real class header once the owner is known.
 */
#ifndef GODHAND_UNKOBJ_H
#define GODHAND_UNKOBJ_H

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

/* Object behind cOmBase_rollChance; flags bit 29 blocks the random roll. */
typedef struct ActObj {
    char pad000[0x9D0];
    unsigned int flags;         /* 0x9D0 */
} ActObj;

/* Object behind CountdownObj_tickIsSpent; timer counts down by the enemy speed rate. */
typedef struct EmTimerObj {
    char pad000[0x630];
    float timer;                /* 0x630 */
} EmTimerObj;

/* Per-level 1-in-N chance table used by Level_rollChance / cOmBase_rollChance. */
typedef struct RndRateTbl {
    int rate[6];
} RndRateTbl;

extern RndRateTbl D_00427CD8;

#endif
