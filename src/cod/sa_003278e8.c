/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
extern int Obj33C8_GetField_CC(int a0);
extern short Obj33C8_GetShortArrayE2_idx(int a0, int idx);

__attribute__((section(".text.func_003278E8")))
int func_003278E8(char *a0, int idx) {
    if (Obj33C8_GetField_CC(*(int*)(a0 + 4)) <= 0) {
        return -0x80;
    }
    if ((unsigned int)(*(unsigned char*)(a0 + 1) - 2) < 2) {
        return Obj33C8_GetShortArrayE2_idx(*(int*)(a0 + 4), idx);
    }
    return -0x80;
}
