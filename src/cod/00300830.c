/* sn-2.95.3-136: kill every live emitter slot (EmitterAllKill, 0x300848);
 * same loop as Esp_killByGroup without the group mask. */

#define EMITTER_SLOT_NUM   0x100
#define EMITTER_SLOT_SIZE  0x260

extern int D_00741940[];                /* bit set: slot in use */
extern int D_00741960[];                /* bit set: slot paused */
extern int D_00741980[];                /* bit set: slot hidden */
extern unsigned char D_0071B940[];      /* the 0x100 emitter slots, 0x260 bytes each */
extern void func_00302918(void *p);

__attribute__((section(".text.EmitterAllKill")))
void EmitterAllKill(void) {
    unsigned char *p;
    int i;
    unsigned int bit;
    int w;

    for (i = 0; i < EMITTER_SLOT_NUM; i++) {
        w = (unsigned int)i >> 5;
        bit = 0x80000000u >> (i & 0x1F);
        if ((D_00741940[w] & bit) == 0) goto next;
        if ((D_00741960[w] & bit) != 0) goto next;
        if ((D_00741980[w] & bit) != 0) goto next;
        p = D_0071B940 + i * EMITTER_SLOT_SIZE;
        func_00302918(p);
next: ;
    }
}
