/* sn-2.95.3-136: plain straight check; a flush is left to the straight-flush checks. */

#include "godhand/Poker.h"

extern void func_001DBF18(Poker *work, unsigned short *nSuit0, unsigned short *nSuit1,
                          unsigned short *nSuit2, unsigned short *nSuit3);
extern void func_001DBFB8(Poker *work, unsigned short *rank0, unsigned short *num0,
                          unsigned short *rank1, unsigned short *num1,
                          unsigned short *rank2, unsigned short *num2,
                          unsigned short *rank3, unsigned short *num3,
                          unsigned short *rank4, unsigned short *num4);

__attribute__((section(".text.func_001DC798")))
int func_001DC798(Poker *work)
{
    unsigned short rank[5];
    unsigned short num[5];
    unsigned short nSuit[4];
    PokerStraightTbl10 tbl;
    int i;
    int k;

    func_001DBFB8(work, &rank[0], &num[0], &rank[1], &num[1], &rank[2], &num[2],
                  &rank[3], &num[3], &rank[4], &num[4]);
    func_001DBF18(work, &nSuit[0], &nSuit[1], &nSuit[2], &nSuit[3]);
    if (nSuit[0] == 5 || nSuit[1] == 5 || nSuit[2] == 5 || nSuit[3] == 5) {
        return 0;
    }
    tbl = D_0042B4D0;
    for (k = 0; k < 10; k++) {
        if (rank[0] == tbl.rank[k][0] && rank[1] == tbl.rank[k][1] &&
            rank[2] == tbl.rank[k][2] && rank[3] == tbl.rank[k][3] &&
            rank[4] == tbl.rank[k][4]) {
            for (i = 0; i < 5; i++) {
                work->hand[i]->flags |= 4;
            }
            return 1;
        }
    }
    return 0;
}
