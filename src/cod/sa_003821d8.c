/* sn-2.95.3-136: func_003821D8, push every channel's volume to the mixer; when func_00382850 reports
 * the list is active, muted channels are sent -960 instead. */
typedef struct ChList3821D8 {
    char unk00[8];
    int count;                  /* 0x08 */
    char unk0C[0x14];
    void *mixer;                /* 0x20 */
} ChList3821D8;

typedef struct Ch3821D8 {
    char unk00[4];
    short vol[0x16];            /* 0x04, 1-based */
    char unk30[0x18];           /* 0x30 start of the channel list header */
    unsigned char mute[1];      /* 0x48, 1-based */
} Ch3821D8;

extern int func_00382850(void *self, ChList3821D8 *list);
extern void func_0032EC78(void *mixer, int ch, int vol);

__attribute__((section(".text.func_003821D8")))
void func_003821D8(void *self, Ch3821D8 *ch)
{
    ChList3821D8 *list = (ChList3821D8 *)ch->unk30;
    int i;

    if (func_00382850(self, list) != 0) {
        for (i = 0; i < list->count; i++) {
            if (ch->mute[i + 1])
                func_0032EC78(list->mixer, i, -0x3C0);
            else
                func_0032EC78(list->mixer, i, ch->vol[i + 1]);
        }
    } else {
        for (i = 0; i < list->count; i++)
            func_0032EC78(list->mixer, i, ch->vol[i + 1]);
    }
}
