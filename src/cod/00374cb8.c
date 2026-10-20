/* sn-2.95.3-136 matched (permuter zero from batch23_nm). */

typedef struct {
    char b[0x30];
} SoundBlk48;

typedef struct {
    short count;
    short pad;
    char *data;
    char rest[0x18];
} SoundSlot32;

extern unsigned char D_0076DF10[];
extern unsigned char D_0076EA50[];
extern void InitSoundBlock_374D98(short a0, short a1, short *a2);
extern void InitSoundEntry_375B90(short a0, short a1, short *a2);

__attribute__((section(".text.func_00374CB8")))
int func_00374CB8(short a0, short a1, short *a2)
{
    SoundSlot32 *ent;
    char *src;

    ent = &((SoundSlot32 *)D_0076DF10)[a0];
    if (a1 < ent->count) {
        src = ent->data;
        src = src + (a1 * 0x30);
        if (((*((unsigned short *)(src + 0xE))) & 0x8000) == 0) {
            *((SoundBlk48 *)a2) = *((SoundBlk48 *)src);
            a2[0] = a0;
            a2[1] = a1;
            return 0;
        }
    }
    InitSoundBlock_374D98(a0, a1, a2);
    return -1;
}

__attribute__((section(".text.func_00375AB0")))
int func_00375AB0(short a0, short a1, short *a2)
{
    char *ent;
    char *src;

    ent = (char *)&((SoundSlot32 *)D_0076EA50)[a0];
    /* twin uses +0x14 count and +0x18 data vs SoundSlot32 layout */
    if (a1 < *(short *)(ent + 0x14)) {
        src = *(char **)(ent + 0x18);
        src = src + (a1 * 0x30);
        if (((*((unsigned short *)(src + 0xE))) & 0x8000) == 0) {
            *((SoundBlk48 *)a2) = *((SoundBlk48 *)src);
            a2[0] = a0;
            a2[1] = a1;
            return 0;
        }
    }
    InitSoundEntry_375B90(a0, a1, a2);
    return -1;
}
