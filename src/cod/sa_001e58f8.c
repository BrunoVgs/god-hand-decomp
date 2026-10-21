/* sn-2.95.3-136 matched TU. */
#include "godhand/Slot2.h"

/* The nine winning symbol triples, one per row of the pay table. */
typedef struct Slot2LineTbl {
    int sym[9][3];
} Slot2LineTbl;

extern Slot2LineTbl D_0042B9D8;

/* Look for a winning triple along one pay line (row a of reel 0, b of reel 1,
 * c of reel 2) and pick the prize screen from the matching table row. */
#define SLOT2_JUDGE_LINE(a, b, c)                                         \
    for (i = 0; i < 9; i++) {                                             \
        if (self->reel[0].sym[a] == tbl.sym[i][0] &&                      \
            self->reel[1].sym[b] == tbl.sym[i][1] &&                      \
            self->reel[2].sym[c] == tbl.sym[i][2]) {                      \
            switch (i) {                                                  \
            case 0:                                                       \
                self->state = 3;                                          \
                self->step = 1;                                           \
                break;                                                    \
            case 1:                                                       \
                self->state = 3;                                          \
                self->step = 2;                                           \
                break;                                                    \
            case 2:                                                       \
                self->phase = 0;                                          \
                self->state = 3;                                          \
                self->step = 3;                                           \
                return;                                                   \
            default:                                                      \
                self->state = 3;                                          \
                self->step = 4;                                           \
                break;                                                    \
            }                                                             \
            self->phase = 0;                                              \
            return;                                                       \
        }                                                                 \
    }

/* Slot2 result: check the pay lines the bet level opens, set the prize screen. */
__attribute__((section(".text.Slot2_JudgeLines")))
void Slot2_JudgeLines(Slot2 *self) {
    Slot2LineTbl tbl = D_0042B9D8;
    int i;

    switch (self->betLv) {
    case 3:
        SLOT2_JUDGE_LINE(0, 1, 2);
        SLOT2_JUDGE_LINE(2, 1, 0);
    case 2:
        SLOT2_JUDGE_LINE(0, 0, 0);
        SLOT2_JUDGE_LINE(2, 2, 2);
    case 1:
        SLOT2_JUDGE_LINE(1, 1, 1);
    }
    self->state = 3;
    self->step = 5;
    self->phase = 0;
}
