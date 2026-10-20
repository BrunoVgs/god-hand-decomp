#include "godhand/seqNode.h"
#include "godhand/cModel.h"
extern void *Obj0000_Set_Field_80_372C68(void *arg0);


__attribute__((section(".text.func_003757A0")))
void func_003757A0(int init, int prio)
{
    if (prio == 0xFFFF) {
        if (init) {
            SndVoiceNode *p = D_0076A600;
            int i = 2;
            do {
                Obj0000_Set_Field_80_372C68(p);
                p++;
            } while (i-- != 0);
        } else {
            if (D_0076A600 != 0) {
                SndVoiceNode *p = D_0076A600 + 3;
                if (p != D_0076A600) {
                    do {
                        p--;
                        ((void (*)(void *, int))p->vt[1].pfn)((char *)p + p->vt[1].delta, 0);
                    } while (p != D_0076A600);
                }
            }
        }
    }
}
