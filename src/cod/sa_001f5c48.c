/* sn-2.95.3-136: NM closer handoff. */
extern void cSnd_BgmEventFade(void *snd, int a1, float f12, float f13, float f14);
extern int cIDBase_release(void *p);
extern void cHeap_free(void *heap, void *block);
extern int D_007474B0;
extern char D_005FEE00[];
extern int *D_003C2388;

__attribute__((section(".text.JukeBox_Release")))
void JukeBox_Release(char *self)
{
    char *s0 = self;
    int *v0;
    void *block;

    D_007474B0 = 0;
    cSnd_BgmEventFade(D_005FEE00, *(int *)(s0 + 0x24), 20.0f, 0.0f, -1.0f);
    cIDBase_release(s0 + 0x30);
    v0 = D_003C2388;
    *(int *)((char *)v0 + 0xF4) = 0;
    *(int *)((char *)v0 + 0xF0) = 0;
    block = *(void **)(s0 + 0x80);
    if (block != 0)
        cHeap_free(*(void **)((char *)block - 0x20), block);
}
