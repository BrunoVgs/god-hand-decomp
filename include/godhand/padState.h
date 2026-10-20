#ifndef GODHAND_PADSTATE_H
#define GODHAND_PADSTATE_H

/* Pad block. Reading it as a struct global gives the retail pattern (hi half kept in a
 * register, lo re-added per use); a char-pointer view folds the lo into the load instead. */
typedef struct {
    char pad[0x1A0];
    long trg;                           /* 0x1A0 trigger bits */
    long f1A8;
    long rep;                           /* 0x1B0 repeat bits */
} PadState;

extern PadState D_007474A0;

#endif /* GODHAND_PADSTATE_H */
