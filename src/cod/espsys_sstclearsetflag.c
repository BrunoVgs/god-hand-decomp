/* espSys_sstClearSetFlag — reset effect slot 0x40 (group 2) via Effect_killByModeB,
 * then clear the flag word at 0x414.  sn-2.95.3-136. */

extern void Effect_killByModeB(int, int);

__attribute__((section(".text.espSys_sstClearSetFlag")))
void espSys_sstClearSetFlag(void *a0) {
    Effect_killByModeB(0x40, 2);
    *(int *)((char *)a0 + 0x414) = 0;
}
