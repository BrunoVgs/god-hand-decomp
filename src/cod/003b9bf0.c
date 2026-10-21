/* cygnus-2.96: func_003B9BF0, per-frame stream decoder step: start it in state 1, then track the
 * decoded sample count in state 2 until the decoder reports done (3). */
typedef struct SndStream {
    char unk00[4];
    int state;                  /* 0x04 */
    char unk08[0x10];
    int total;                  /* 0x18 */
    char unk1C[0x6C];
    int played;                 /* 0x88 */
    char unk8C[4];
    int delta;                  /* 0x90 */
    int pos;                    /* 0x94 */
    char unk98[0x28];
    int dec;                    /* 0xC0 */
} SndStream;

extern int func_003BA800(int dec);
extern void func_003BA058(int dec);
extern void func_003BA000(int dec);
extern void func_003BA0C8(int dec);
extern void func_003BA830(int dec, int *pos, int *bytes);

__attribute__((section(".text.func_003B9BF0")))
void func_003B9BF0(SndStream *s)
{
    int dec = s->dec;
    int pos, bytes;

    if (func_003BA800(dec) == 0) {
        s->played = 0;
        func_003BA058(dec);
    }
    if (s->state == 1) {
        s->played = 0;
        func_003BA000(dec);
        s->state = 2;
    } else if (s->state == 2) {
        func_003BA0C8(dec);
        func_003BA830(dec, &pos, &bytes);
        s->pos = pos;
        s->delta = bytes / 4 - s->played;
        s->played += s->delta;
        if (func_003BA800(dec) == 3) {
            func_003BA058(dec);
            s->state = 0;
            s->total = bytes / 4;
        }
    }
}
