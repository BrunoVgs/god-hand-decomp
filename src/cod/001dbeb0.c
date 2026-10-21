/* sn-2.95.3-136 matched TU. */
#include "godhand/Poker.h"

#define BLACKJACKCARD_OFFSET(field)  ((int)&((BlackJackCard *)0)->field)
/* Kept raw: retail walks a pointer to each card's flags word and reaches the
   card through it (obj at -4); walking a BlackJackCard pointer moves every
   offset by 4 and no longer matches. */
#define CARD_OF_FLAGS(f)  ((BlackJackCard *)((char *)(f) - BLACKJACKCARD_OFFSET(flags)))

/* Put all 52 cards back in the deck face down and empty the hand. */
__attribute__((section(".text.Poker_resetDeck")))
void Poker_resetDeck(Poker *self) {
    unsigned int *flags = &self->deck[0].flags;
    int i;
    int j;
    i = POKER_DECK_NUM - 1;
    /* Preserve loop-entry alignment without hoisting the state constant. */
    do {
loop:
        ;
    } while (0);
    CARD_OF_FLAGS(flags)->obj->flags |= BLACKJACK_CARD_FACE_DOWN;
    *flags = POKER_CARD_RESET;
    CARD_OF_FLAGS(flags)->obj->unk104 = 0;
    flags += sizeof(BlackJackCard) / sizeof(*flags);
    if (--i >= 0) goto loop;
    for (j = POKER_HAND_NUM - 1; j >= 0; j--) {
        self->hand[j] = 0;
    }
}
