/* sn-2.95.3-136, as=sn (ps2eeas keeps the mtc1 hazard nops): dispatch the pending update flags at +6, then clear them. */
extern char D_0076A600[];
extern void func_0037D3C8(char *self);
extern void func_0037D680(char *self);
extern void func_0037D728(char *self);
extern void func_0037D558(char *self);
extern void func_0037C720(char *self);
extern void func_003738A0(void *node, int a1, float w);
extern void UpdateSequenceNodeWeighted_373560(void *node, int a1, float w);

__attribute__((section(".text.func_0037CCE0")))
void func_0037CCE0(char *self)
{
    if (self[5] & 8) {
        if (*(unsigned short *)(self + 6) & 1) {
            func_0037D3C8(self);
            func_003738A0(D_0076A600 + *(short *)(self + 2) * 0x84, -1,
                          (short)*(unsigned short *)(self + 0x3E) >> 8);
            UpdateSequenceNodeWeighted_373560(D_0076A600 + *(short *)(self + 2) * 0x84, -1,
                                              (short)*(unsigned short *)(self + 0x3E) >> 8);
        }
        if (*(unsigned short *)(self + 6) & 2) {
            func_0037D680(self);
            func_0037C720(self);
        }
    } else {
        if (*(unsigned short *)(self + 6) & 1) {
            func_0037D3C8(self);
        }
        if (*(unsigned short *)(self + 6) & 2) {
            func_0037D680(self);
        }
        if (*(unsigned short *)(self + 6) & 4) {
            func_0037D728(self);
        }
        if (*(unsigned short *)(self + 6) & 8) {
            func_0037D558(self);
        }
    }
    *(unsigned short *)(self + 6) = 0;
}
