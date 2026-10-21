/* cygnus-2.96 matched TU. */
#include "godhand/criSj.h"

extern Sint8 D_0045A060[];
extern Sint8 D_0045A068[];
extern Sint8 D_0045A070[];

typedef struct SfxZmvTagState {
    int reserved[2];
    SjTagRec input;
    int reserved14;
    SjTagRec header;
    int reserved24;
    SjTagRec frame;
} SfxZmvTagState;

/* Find the header and frame tag chunks in the input stream. */
__attribute__((section(".text.sfxzmv_SetTagGrp")))
void sfxzmv_SetTagGrp(SfxZmvTagState *state)
{
    SjChunk input;
    SjChunk found;
    SjTagRec *header = &state->header;
    SjTagRec *frame = &state->frame;
    SjTagRec *source = &state->input;
    Sint8 *data = source->ck.data;

    if (data == 0) {
        header->ck.len = 0;
        header->set = 1;
        header->ck.data = 0;
        frame->set = 1;
        frame->ck.data = 0;
        frame->ck.len = 0;
        return;
    }
    input.data = data;
    input.len = source->ck.len;
    SJ_SearchTag(&input, D_0045A060, D_0045A068, &found);
    header->ck.data = found.data;
    header->ck.len = found.len;
    header->set = 1;
    SJ_SearchTag(&input, D_0045A070, D_0045A068, &found);
    frame->set = 1;
    frame->ck.data = found.data;
    frame->ck.len = found.len;
}
