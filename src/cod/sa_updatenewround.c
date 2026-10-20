/* sn-2.95.3-136: NM closer handoff. */
/* halt demote BlackJack_UpdateNewRound */
extern void func_001D4670(void *self);
extern void BlackJackId_SetDefaultDisp(void *self);
extern void CustomIDWork_SetNumber_1D5760(void *self, int n);
extern int cCoreSave_getGold(void *save);
extern void func_001D5780(void *self, int gold);
extern char D_00569B70[];

__attribute__((section(".text.BlackJack_UpdateNewRound")))
void BlackJack_UpdateNewRound(void *self)
{
    int gold;
    unsigned int flags;
    long tmp;

    *(int *)((char *)self + 0x1814) = 0;
    *(int *)((char *)self + 0x1818) = 0;
    *(short *)((char *)self + 0x17FC) = 0;
    *(short *)((char *)self + 0x17FE) = 0;
    func_001D4670(self);
    BlackJackId_SetDefaultDisp(self);
    CustomIDWork_SetNumber_1D5760(self, 0);
    gold = cCoreSave_getGold(D_00569B70);
    func_001D5780(self, gold);
    flags = *(unsigned int *)((char *)self + 0x1800);
    tmp = flags;
    tmp = tmp >> 3;
    tmp = tmp & 1;
    if (tmp != 0) {
        *(int *)((char *)self + 0x1808) = 0;
        *(int *)((char *)self + 0x1804) = 2;
    } else {
        *(int *)((char *)self + 0x1808) = 0;
        *(int *)((char *)self + 0x1804) = 1;
    }
    *(int *)((char *)self + 0x1800) = 0;
}

