/* sn-2.95.3-136: blackjack hand totals (0x1D4720..). */

#include "godhand/BlackJack.h"

__attribute__((section(".text.func_001D4720")))
int func_001D4720(BlackJack *work)
{
    int score = 0;
    unsigned short aces;
    int i;
    int rank;

    for (i = 0; i < work->dealSlot; i++) {
        rank = work->handA[i]->obj->rank;
        if (rank != 0) {
            if (rank >= 1 && rank <= 9) {
                score += rank + 1;
            } else {
                score += 10;
            }
        }
    }
    aces = 0;
    for (i = 0; i < work->dealSlot; i++) {
        if (work->handA[i]->obj->rank == 0) {
            aces++;
        }
    }
    while (aces != 0) {
        aces--;
        if (aces == 0 && score + 11 < 22) {
            score += 11;
        } else {
            do { score++; } while (0);
        }
    }
    return score;
}

__attribute__((section(".text.func_001D47E8")))
int func_001D47E8(BlackJack *work)
{
    int score = 0;
    unsigned short aces;
    int i;
    int rank;

    for (i = 0; i < work->dealSlotB; i++) {
        rank = work->handB[i]->obj->rank;
        if (rank != 0) {
            if (rank >= 1 && rank <= 9) {
                score += rank + 1;
            } else {
                score += 10;
            }
        }
    }
    aces = 0;
    for (i = 0; i < work->dealSlotB; i++) {
        if (work->handB[i]->obj->rank == 0) {
            aces++;
        }
    }
    while (aces != 0) {
        aces--;
        if (aces == 0 && score + 11 < 22) {
            score += 11;
        } else {
            do { score++; } while (0);
        }
    }
    return score;
}
